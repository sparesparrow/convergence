
# Baseline software architecture patterns


### Model of operation

`Convergence` operates on an applied blackboard system where multiple agents contribute and interact with each other. Each agent has a specialized role, be it monitoring, processing, or providing output. They work collectively to provide a personalized and efficient assistance to the user. The blackboard system enables a seamless interaction between these agents, orchestrating their collective knowledge and resources to solve complex problems and provide comprehensive solutions.

### Blackboard Operations

In the context of the `Convergence`, blackboard operations mainly involve:
1. Writing: This involves posting of new problems, tasks, and updates by the agents onto the blackboard. The agents can also add new suggestions or information pertinent to the user's activities or needs.
2. Reading: The agents are continuously monitoring the blackboard to identify any new problems or tasks they can solve. They also read the blackboard to gather data and information for their internal processing.
3. Erasure: Once a task is completed or a problem is solved, the corresponding entries from the blackboard are removed. This keeps the blackboard clean and updated.

### Control Shell

The control shell in our system is responsible for managing the execution of tasks and ensuring smooth interaction between the agents. It decides the order of agent execution based on a set of predefined rules and priorities. These rules can be modified based on the context and user needs. The control shell also ensures that all agent activities are properly synchronized and that the blackboard remains a reliable source of information.

### Knowledge Source Activation

The activation of knowledge sources (KSs) or agents in the `Convergence` is controlled by the control shell. The KSs can be activated based on certain conditions or triggers. For example, the "Focused Activity Monitoring Agent" can be activated when the user has been working for a certain duration without a break. The triggers for each KS are predefined and can be updated based on user preferences or feedback.

### Blackboard Data Structures

The blackboard in the `Convergence` is a dynamic data structure that holds various types of information. It is divided into different sections or spaces, each dedicated to a particular type of information. For example, there can be a space for user activities, another for user mood or mental health data, etc. The structure of the blackboard can evolve based on the requirements of the system and the agents.

### Blackboard System Benefits

The blackboard system provides a flexible architecture for developing a complex AI assistant. It allows for easy incorporation of new knowledge sources or agents, making the system highly scalable. It also facilitates efficient handling of complex tasks and problems that require the collective expertise of multiple agents. Additionally, the blackboard system provides a transparent view of the problem-solving process, making it easier to debug and improve the system.

### Blackboard System Agent Integration

The Homework Wellness Assistant employs a Blackboard system to manage inter-agent communication and decision making. This system allows agents to access and modify a common knowledge base, facilitating coordinated responses to user activities and input.

Within this Blackboard system, each agent, regardless of its layer, checks the Blackboard for changes in the data that it is interested in. When an agent identifies relevant changes or conditions, it processes the information, makes decisions, and may post its own data back to the Blackboard. This process continues as long as agents keep identifying relevant changes on the Blackboard.

Agent-specific data and Blackboard interaction rules are defined in the agent's configuration. These configuration details guide the agent's decision-making process, ensuring that it only interacts with relevant data and contributes useful information back to the Blackboard.
Blackboard Data

The Blackboard primarily contains user-related data, which is managed by the "PersonalizationAgent." However, any agent can post data to the Blackboard if it is relevant to the system's operation. This data includes, but is not limited to, user activities, system events, and agent decisions.

## Blackboard system

**A blackboard-system application consists of three major components:**

1. The `software specialist modules`, which are called knowledge sources (KSs). Like the human experts at a blackboard, each knowledge source provides specific expertise needed by the application.
2. The blackboard, a `shared repository` of problems, partial solutions, suggestions, and contributed information. The blackboard can be thought of as a dynamic "library" of contributions to the current problem that have been recently "published" by other knowledge sources.
3. The `control shell`, which controls the flow of problem-solving activity in the system. Just as the eager human specialists need a moderator to prevent them from trampling each other in a mad dash to grab the chalk, KSs need a mechanism to organize their use in the most effective and coherent fashion. In a blackboard system, this is provided by the control shell.

*Knowledge base for the user-ai interaction design:*

Blackboard system - "https://en.wikipedia.org/wiki/Blackboard_system"
Autonomous decentralized system - "https://en.wikipedia.org/wiki/Autonomous_decentralized_system"
Artificial intelligence systems integration - "https://en.wikipedia.org/wiki/Artificial_intelligence_systems_integration"
Message passing - "https://en.wikipedia.org/wiki/Message_passing"
Pandemonium architecture - "https://en.wikipedia.org/wiki/Pandemonium_architecture"
Tuple space - "https://en.wikipedia.org/wiki/Tuple_space"


## Autonomous decentralized system

An autonomous decentralized system (or ADS) is a decentralized system composed of modules or components that are designed to operate independently but are capable of interacting with each other to meet the overall goal of the system. This design paradigm enables the system to continue to function in the event of component failures. It also enables maintenance and repair to be carried out while the system remains operational. Autonomous decentralized systems have a number of applications including industrial production lines, railway signalling and robotics.

The ADS has been recently expanded from control applications to service application and embedded systems, thus autonomous decentralized service systems and autonomous decentralized device systems.
An ADS is a decoupled architecture where each component or subsystem communicates by message passing using shared data fields. A unique feature of the ADS is that there is no central operating system or coordinator. Instead each subsystem manages its own functionality and its coordination with other subsystems. When a subsystem needs to interact with other subsystems it broadcasts the shared data fields containing the request to all other subsystems. This broadcast does not include the identification or address of any other subsystem. Rather the other subsystems will, depending on their purpose and function, receive the broadcast message and make their own determination on what action (if any) to take.

As ADS moves into the service-oriented architecture (SOA) or ADSS (Autonomous Decentralized Service System), the data transmission can be carried out by ESB (Enterprise Service Bus), and each agent can a service that receives data from the ESB and acts according to the service specification. The results are again transmitted by the ESB to other autonomous agents.

An ADS is also similar to a blackboard system used in AI where a collection of agents will act upon seeing any data change in the common blackboard.

An ADS may include human in the loop, with both human and autonomous agents both co-learn at the same time to perform the system functionality.

