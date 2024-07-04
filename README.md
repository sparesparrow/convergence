# `Convergence`

Software architecture is designed around the principle of the Blackboard system. This design pattern facilitates the efficient collaboration and communication between various intelligent agents in the system. The Blackboard system acts as a shared knowledge base, where agents can add, modify, and retrieve information. 
- The Blackboard system allows for an effective mechanism for multi-agent cooperation, where each agent can perform its tasks independently and communicate the results through the Blackboard. This way, the agents can work concurrently, handling their tasks in parallel, and respond to changes in the user's context in a dynamic, real-time manner.
- The Blackboard system facilitates a more structured agent hierarchy. The Input Layer agents, such as the "EnvironmentMonitoringAgent" and the "LanguageProcessingAgent", can capture user input and events and add this information to the Blackboard. The Processing Layer agents can then access this information from the Blackboard, process it, and add the results back to the Blackboard. The Output Layer agents can then access the results from the Blackboard and provide feedback or guidance to the user.
- The Blackboard system also provides a flexible architecture for adding or modifying the agents. New agents can be easily integrated into the system by connecting them to the Blackboard. The behavior of existing agents can be modified by changing their interaction with the Blackboard.
- The user's profile context is now also managed through the Blackboard. The "PersonalizationAgent" can add the user profile context to the Blackboard, and other agents can access this context information from the Blackboard to make more informed decisions.

## Applied Blackboard System
- The blackboard model can be implemented as a shared database where the agents can read and write data. The agents can be triggered based on events or changes in the data on the blackboard. Each agent will have a specific role and will be responsible for a particular task or process. For instance, an agent could be responsible for monitoring the user's activity, while another agent could be tasked with analyzing the user's psychological profile.
- The blackboard will store all relevant information about the user's activity, profile, and interactions with the system. This information can be updated and read by the agents. The data stored on the blackboard will include the user's actions, historical data, psychological profile, etc.
- Agents can also post tasks or queries on the blackboard, which other agents can pick up and process. For example, an agent could post a task to analyze the user's current activity, and another agent could pick up this task, perform the analysis, and post the results back on the blackboard.
- The blackboard system would allow for dynamic and flexible interaction between the agents, leading to a more robust and adaptable system. The agents can work in parallel, processing the data independently and concurrently, leading to a more efficient system.
- 
C++ interface classes for the Blackboard system:
```cpp
/* This interface represents an observer that monitors changes in the blackboard */
class IBlackboardObserver {
public:
    virtual ~IBlackboardObserver() = default;
    virtual void onBlackboardChanged(IBlackboard* blackboard) = 0;
};
/* This interface represents a query that can be posted on the blackboard and processed by an agent */
class IQuery {
public:
    virtual ~IQuery() = default;
    virtual std::string getQueryText() const = 0;
    virtual void processQuery(IBlackboard* blackboard) = 0;
};
/* Updating the IAgent interface to include methods for processing a query */
class IAgent {
public:
    virtual ~IAgent() = default;
    virtual void performAction(IBlackboard* blackboard) = 0;
    virtual void processQuery(IQuery* query, IBlackboard* blackboard) = 0;
};
/* Updating the IBlackboard interface to include methods for adding an observer and posting a query */
class IBlackboard {
public:
    virtual ~IBlackboard() = default;
    virtual void addMessage(IMessage* message) = 0;
    virtual void modifyMessage(IMessage* message, const std::string& newText) = 0;
    virtual std::vector<IMessage*> getAllMessages() const = 0;
    virtual void addObserver(IBlackboardObserver* observer) = 0;
    virtual void postQuery(IQuery* query) = 0;
};
/* This class represents an agent in the Blackboard system. It inherits from the IAgent interface and adds methods for accessing and modifying the blackboard. */
class BlackboardAgent : public IAgent {
public:
    BlackboardAgent(IBlackboard* blackboard) : blackboard(blackboard) {}
    void performAction() override {
        // Implementation of action specific to the agent
    }
protected:
    IBlackboard* blackboard;
};
/* This class represents the blackboard in the Blackboard system. It inherits from the IBlackboard interface and adds methods for managing the messages on the blackboard. */
class Blackboard : public IBlackboard {
public:
    void addMessage(IMessage* message) override {
        // Add the message to the blackboard
    }
    void modifyMessage(IMessage* message, const std::string& newText) override {
        // Modify the message on the blackboard
    }
    std::vector<IMessage*> getAllMessages() const override {
        // Retrieve all messages from the blackboard
    }
protected:
    std::vector<IMessage*> messages;
};
/* This class represents the control component in the Blackboard system. It inherits from the IControlComponent interface and adds methods for managing the agents and the blackboard. */
class BlackboardControlComponent : public IControlComponent {
public:
    BlackboardControlComponent(IBlackboard* blackboard) : blackboard(blackboard) {}
    void addAgent(IAgent* agent) override {
        // Add the agent to the control component
    }
    void start() override {
        // Start the operation of the system with the given blackboard
    }
protected:
    IBlackboard* blackboard;
    std::vector<IAgent*> agents;
};
/* The Message class represents a piece of data in the Blackboard system. */
class Message : public IMessage {
public:
    std::string getText() const override;
    void setText(const std::string& text) override;
};
/* The Blackboard class acts as the common data storage and communication medium for all agents. */
class Blackboard : public IBlackboard {
public:
    void addMessage(IMessage* message) override;
    void modifyMessage(IMessage* message, const std::string& newText) override;
    std::vector<IMessage*> getAllMessages() const override;
};
/* The Agent class represents an entity that interacts with the Blackboard, making decisions based on the data in the Blackboard and posting its own data. */
class Agent : public IAgent {
public:
    void performAction(IBlackboard* blackboard) override;
};
/* The ControlComponent class manages the operation of the Blackboard system, including the addition of agents and the initiation of system operation. */
class ControlComponent : public IControlComponent {
public:
    void addAgent(IAgent* agent) override;
    void start(IBlackboard* blackboard) override;
};
```

# Components and features

## OpenAI API Handler
Convergence will utilize GPT language models to automate the development process as much as possible. For example, if editing a source code file, the keyboard shortcut would trigger a sequence of actions (generally OpenAI GPT API prompts) on the file's content, providing different kinds of results like Explain Code, Code Readability Review, Code Syntax Correction, Found Bugs, Suggested Improvements, etc. For all those results, the user will then have options like Accept Suggestions, Copy to Clipboard, Save to File, Use as GPT Input, etc.

## TextContentAgents
Text Content Processing OpenAI Agent Interface
`TextContentAgents` is a Qt6/QML/C++ component that demonstrates a multi-agent setup for processing user input. It features a text input area where users can provide raw text, which will be processed by a series of agents. Each agent has its own role in the processing pipeline, and their output is used to either update the UI or feed into other agents for further processing.

- User-friendly interface for input and agent visualization
- A set of agents with specific tasks for processing the user input
- An OpenAI API integration for processing requests and responses
- Dynamic agent response processing and delegation to other agents
- Customizable agent setup for extending or modifying the processing pipeline
- The component uses Qt and QML to create a responsive user interface and agent components. The agent components are instances of the Agent class, which inherits from QObject. They use the OpenAI API to process the user's input and return a response. The agents are connected to each other using the Qt signals and slots mechanism, allowing them to asynchronously communicate and process data.

Example Flow
1. The user enters raw text in the input area and clicks the "Start Processing" button.
2. The processRawText() function iterates through the list of agents to find the "DataCategoryDetector" agent and sends the user input to it.
3. The "DataCategoryDetector" agent processes the input and returns a key:value pairs describing the input text.
4. The onResponseReceived() function is called, and based on the agent's name, it processes the response and delegates tasks to other agents accordingly.
5. Other agents in the pipeline process their tasks and return responses, which are handled by the onResponseReceived() function.

## Serialization of communication using flatbuffers
- The communication between agents is serialized using flatbuffers. This allows for efficient communication between agents, as well as easy serialization and deserialization of data.

Blackboard.fbs
```fbs
namespace Blackboard;

enum MessageChannel: byte
{
    OpenAIApiHandler,
    LocalNetwork,
    Blackboard,
}
```
LocalNetwork.fbs
```fbs
namespace LocalNetwork;

enum RequestType: byte
{
    InvalidRequest,
    PeerDiscoveryRequest,
    DeviceInfoRequest,
    AudioStreamRequest,
}
enum ResponseType: byte
{
    InvalidResponse,
    PeerDiscoveryResponse,
    DeviceInfoResponse,
    AudioStreamResponse,
}
table PeerDiscoveryRequest {
    ssrcId: int;
    svcAnnounces: [int];
}
table PeerDiscoveryResponse {
    ssrcId: int;
}
table DeviceInfoRequest
{}
table DeviceInfoResponse {
    deviceTypeId: int;
}
table AudioStreamRequest
{
    actionId: int;
}
table AudioStreamResponse
{
    jobId: int;
}
union RequestPayload
{
    PeerDiscoveryRequest,
    DeviceInfoRequest,
    AudioStreamRequest,
}
union ResponsePayload
{
    PeerDiscoveryResponse,
    DeviceInfoResponse,
    AudioStreamResponse,
}
table Request
{
  type:RequestType;
  data:RequestPayload;
}
table Response
{
  type:ResponseType;
  data:ResponsePayload;
}

root_type Request;
root_type Response;
```

OpenAIApiHandler.fbs
```fbs
namespace OpenAIApiHandler;

enum RequestType: byte
{
    ChatCompletionRequest,
}
enum ResponseType: byte
{
    ChatCompletionResponse,
}

table ChatUserMessage {
    system: string;
    user: string;
    temperature: float;
    topP: float;
    maxTokens: int;
}

table ChatCompletionRequest {
    message: ChatUserMessage;
    requestorId: int;
}

table ChatCompletionResponse {
    message: string;
    requestorId: int;
}

union RequestPayload
{
    ChatCompletionRequest,
}
union ResponsePayload
{
    ChatCompletionResponse,
}

table Request
{
  type:RequestType;
  data:RequestPayload;
}
table Response
{
  type:ResponseType;
  data:ResponsePayload;
}

root_type Request;
root_type Response;
```

## ConvergentAssistant

ConvergentAssistant is a decentralized system of agents designed to help remote workers manage their mental health and stay organized. The app combines mental health features with a voice assistant to provide personalized support for managing stress, burnout, work-life balance, and productivity.

- Wraps various OpenAI API calls into intelligent agents in order to improve user experience while interacting with the language model, requiring only minimal user's collaboration. 
- The goal is to create a fully autonomous assistant that understands the user's psychological profile and their usual activities, field of their work, their history and plans in order to help them working, learning, keeping mental health, analyze their environment, evaluating near future scenarios and their probabilities, rate user's action, provide guidance, feedback or constructive critic etc.
- The motivation for the user to choose this app over corporate solutions is that the user have full control over their data and privacy, since all the data is stored locally on the user's device and shared with no other party. The requests to the OpenAI API are lacking the user's whole profile context, because they are based on pre-designed templates, resulting in straightforward OpenAI completion prompt that is defined by triggered agent's role in the system. An example of an OpenAI request being sent when triggered by user's activity would be:
  - Agent name: `Focused Activity Monitoring Agent`
  - Agent type: `Monitoring Agent`
  - Triggering agents: `Short Break Agent`, `Social Interaction Agent`, `Guided Meditation Agent`, `Activity Assistant for Work`, `Activity Assistant for Learning`
  - Configured prompt: `Kindly ask the user to take a break. Figure out whether to notify ` { TriggeringAgents } ` and prepare them a trigger input message based on the following context: ` 
  - User Data: `It is 10:00 AM. User has been working on his project for 3 hours without a break. Meeting starts in 30 minutes. Current user's activity is estimated to take 2 more hours. User did not eat yet.`

*In the above example, the `Short Break Agent` and `Activity Assistant for Work` are triggered with a message that leads to a proposal of taking a break and prepare for meeting, letting user choose one of their favorite meal delivery, scheduling lunch activity after meeting, and offering an assistance with their project after lunch. The rest of the configured TriggeringAgents are not triggered, because the User Data contained no relevant reason for a trigger.*

**ConvergentAssistant Modules**
- The app will have daily mood tracking feature to help users monitor their emotional well-being.
- It will offer guided meditation and relaxation exercises to help users manage stress and prevent burnout.
- The app will allow users to set goals and track their progress, helping them stay organized and focused.
- There will be social networking features for remote workers, allowing them to connect with others in similar situations.
- The app will provide work-life balance reminders to help users maintain a healthy balance between work and personal life.
- There will be voice-activated reminders for upcoming meetings and events, making it easier for users to stay on top of their schedule.
- Voice prompts will be available for in-progress tasks and goals, helping users stay focused on their objectives.
- Users will receive voice notifications for incoming emails or messages, allowing them to stay connected without getting distracted.
- The app will integrate with popular calendar, email, and project management apps, making it easy for users to access all their important information in one place.
- Task Management
   - Allow users to create tasks and subtasks with deadlines, and label them with categories or tags.
   - Provide a visual representation of tasks, such as a calendar view or Kanban board, to help users see their workload.
   - Offer reminders and notifications for upcoming deadlines.
- Focus Timer
   - Implement a customizable focus timer using techniques like the Pomodoro Technique or other time management strategies.
   - Allow users to customize work and break durations.
   - Provide optional background sounds or music to help users concentrate during work sessions.
   - Encourage regular breaks to prevent burnout and maintain focus.
- Mindfulness and Meditation Exercises
   - Include a library of guided meditation and mindfulness exercises designed to reduce stress, anxiety, and improve focus.
   - Offer mindfulness exercises that users can practice throughout the day to stay present and focused.
   - Provide progress tracking and reminders to encourage users to practice regularly.
- Habit Tracking
   - Allow users to set goals for healthy habits, such as exercising, sleeping, and eating well.
   - Track users' progress and provide visual representations of progress.
   - Send reminders and notifications to encourage users to maintain healthy habits.
- Personalized Reminders and Prompts
   - Use natural language generation to create personalized reminders and prompts that are designed to capture the user's attention and encourage them to complete their tasks.
   - Use machine learning algorithms to analyze the user's behavior and tailor the prompts and reminders to their individual needs.
### Potential target users of ConvergentAssistant:
- College students who need help managing their workload and staying focused.
- Remote workers who need help maintaining productivity while working from home.
- Freelancers who need help managing their time and completing tasks efficiently.
- Individuals with other neurodevelopmental or mental health disorders, such as anxiety or depression, who struggle with concentration and productivity.
- Small business owners who need help managing multiple tasks and priorities.
- Professionals who work in high-stress environments, such as healthcare or emergency services.
- Individuals who want to develop healthy habits and improve their overall well-being.
- Anyone who wants to improve their productivity and concentration, regardless of their specific background or condition.
## ConvergenceGame
- ConvergentAssistant with Gamification
   - Incorporate gamification elements, such as points, badges, and leaderboards, to motivate users to engage with the app and improve their productivity.
   - Provide rewards for completing tasks or achieving goals, such as extra salary or bonuses.
   - Use four types of reward tokens, each type a different color. The type of reward relate to which kind of a completed task the reward was paid upon. Once in a period, like a month, tokens ar recounted and converted to real-life-consumable bonus reward (i.e. extra money from employer, free days off etc.). Only keeping the (more or less) same ammount from each color will count as a "token value". This prevents hoarding of just one kind of a token.
   - There will be four types of tasks and rewards:
        1. `Red/Blue` - Work-related, with a time limit of 20-40minutes, user has to be focused in order to achieve reward. task description is generated by AI assistant, which has access to user's whole TODO list. Relates to a measurable progress in work project, making the boss happy. Inspired by pomodoro technique (Red is time-limited with a pomodoro countdown, Blue are longer term tasks).
        2. `Yellow` - reward for regular resting - systematic switching to "diffused" mode of the mind, that should follow right after every "focus" related activity. the tokens are taken from user if he refuse to stop working when Pomodoro alert's time over.
        3. `Green` to reward user of doing something good for his health, such as sport activity, or doing something good for his pure happiness, like to really enjoy an evening he/she was long time waiting and looking forward to, instead of cancelling it because of "too much work" or other excuse to not have fun. Working overtime is nice and proactive, but only if that doesn't need to happen too often. Regular overtimes should rather be signed by both sides as an extension to the work agreement if both employer and employee agrees on extending the time worked.
        4. `Black` will be miscelaneous type of activity needed to balance the user's mental stability. This task is designed personally to the user by the AI assistant that cares about user's work-life balance, specifically to fit inside the user's life based on the assistant's observation of the user. Could simply mean just `Turn off the TV and go sleep early today.` Black tokens prevents user from working too much, as well as from lazyness or lacking the mental hygiene.


### Potential target users of ConvergentAssistant:
- College students who need help managing their workload and staying focused.
- Remote workers who need help maintaining productivity while working from home.
- Freelancers who need help managing their time and completing tasks efficiently.
- Individuals with other neurodevelopmental or mental health disorders, such as anxiety or depression, who struggle with concentration and productivity.
- Small business owners who need help managing multiple tasks and priorities.
- Professionals who work in high-stress environments, such as healthcare or emergency services.
- Individuals who want to develop healthy habits and improve their overall well-being.
- Anyone who wants to improve their productivity and concentration, regardless of their specific background or condition.
## Agent hierarchy
Each agent sends its preconfigured API call seamlessly when triggered. Agent hierarchy is chaining the responses received as input to other related agents. Each agent defines its own trigger conditions and a list of other agents receiving the content of the response. Those next-level agents will then evaluate the response, optionally request context information from the locally stored user's profile, and based on their configuration decide whether to "trigger" themselves, in which case sending their own pre-designed API call request, and chaining the received response to their list of related agents. This process continues while agents keep triggering.

## Agent layers:
Input Layer: These agents capture user input and events. Examples include the "EnvironmentMonitoringAgent" and the "LanguageProcessingAgent."
Processing Layer: These agents process the information and make decisions based on input from the Input Layer agents. Examples include the "TaskManagementAgent", "MentalHealthAgent", "FocusAndConcentrationAgent", "LearningAgent", "ScenarioAnalysisAgent", and "EvaluationAgent."
Output Layer: These agents handle communication with the user and provide feedback or guidance. Examples include the "CommunicationAgent" and "PersonalizationAgent."
The user interaction should primarily occur at the "EnvironmentMonitoringAgent" and "LanguageProcessingAgent" levels. These agents capture user input and events and trigger other agents accordingly. The "CommunicationAgent" can also interact with the user as needed. As for the user profile context, it should be primarily managed by the "PersonalizationAgent." Other agents in the Processing Layer can access the user profile context via the "PersonalizationAgent" to make more informed decisions.

## Agent types

### Language Processing Agent
**Layer:** `Input`
**Description:** This agent processes the user's natural language input and sends requests to other agents based on the user's needs and preferences.

### Personalization Agent
**Layer:** `Output`
**Description:** This agent collects and analyzes data about the user's behavior, preferences, and history to provide personalized recommendations and guidance.

### Task Management Agent
**Layer:** `Processing`
**Description:** This agent helps the user manage their tasks and prioritize their work, using a variety of techniques such as goal-based or utility-based decision-making.

### Focus and Concentration Agent
**Layer:** `Processing`
**Description:** This agent provides techniques and exercises to help the user improve their focus and concentration, such as mindfulness or meditation exercises.

### Mental Health Agent
**Layer:** `Processing`
**Description:** This agent monitors the user's mental health and provides support or guidance as needed, such as recommending stress-relief techniques or connecting the user with mental health resources.

### Learning Agent
**Layer:** `Processing`
**Description:** This agent uses feedback from the user to improve its own performance over time, and adapt to the user's changing needs and preferences.

### Scenario Analysis Agent
**Layer:** `Processing`
**Description:** This agent evaluates the user's environment and predicts future scenarios and their probabilities, providing recommendations and guidance based on these predictions.

### Evaluation Agent
**Layer:** `Processing`
**Description:** This agent rates the user's actions and provides feedback or constructive criticism, helping the user to improve their performance and productivity.

### Communication Agent
**Layer:** `Output`
**Description:** This agent facilitates communication between the user and other agents, as well as with external systems or resources.

### Health and Fitness Agent
**Layer:** `Processing`
**Description:** This agent monitors the user's physical health and provides recommendations for maintaining or improving their fitness, such as exercise routines, diet plans, or sleep recommendations.

### Social Interaction Agent
**Layer:** `Processing`
**Description:** This agent helps the user manage their social life and relationships, providing reminders for important events, tracking interactions with friends and family, and suggesting activities to strengthen their connections.

## Features allowing the user to interact with the model may involve implementation of:
1. TTS/STT: While supporting voice input from the user (Whisper STT API), the application maintaints conversation with the user in a way that requires the user to speak as little as possible, and rather asks questions that in best scenario offers a Yes/No answer or gives options to choose from. The user can then choose to answer in their preffered way - voice response, headset button press, mouse click event, dynamically mapped keyboard shortcut, mobile device notification button etc.
2. Android/iOS Share menu: The application can be invoked from the share menu of any application, and the user can share any text with the application. The application will then parse the text, and depending on the content decides whether to:
  - `Plain text`: format and use the contents as an input to the TextCategorizationModel, then use received response to decide an action performed, and whether to notify the user about it.
  - `URL`: based on the protocol in the URL, the application will evaluate the best relevant action to perform, based on the the protocol. For example, if the URL is a `mailto:`, the application will lookup the mail address in the user's mail history, in user's contacts and in assistan's chat history, and will prepare suggested content for a new email to send, or will offer other options with the address, for example setting up a VS Code live share session between the user and the `mailto` contact.
3. Context-aware proactive suggestions: The application can analyze user behavior and the current context to provide timely and relevant suggestions to the user. For example, if the user has been working on a specific project for a while, the assistant can offer to create reminders for breaks or suggest related resources. Alternatively, the application can detect when the user is in a meeting or a presentation and proactively offer features like note-taking, agenda management, or real-time transcription.
4. Gesture-based interaction: The application can support gesture-based interaction through a camera or other sensors, allowing users to control the assistant with simple hand movements or body gestures. This would enable a more natural and intuitive interaction experience, especially for users with accessibility requirements or those in situations where voice or traditional input methods are not suitable.
5. Integration with smart home devices: The application can be integrated with smart home devices, such as Amazon Alexa, Google Home, or Apple HomeKit, enabling users to interact with the assistant through their existing smart home ecosystems. This would allow users to control smart devices, receive notifications, and access the assistant's features using their preferred smart home platform.


# 'Pull requests' from [Hard-Coder](https://chatgpt.com/share/00f8b8dd-9ddf-4db9-b335-21cac0f07e77):

- [**update.md**](update.md)
- [**update1.md**](update1.md)
- [**update2.md**](update2.md)