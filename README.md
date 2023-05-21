# Convergence

Convergence will utilize GPT language models to automate the development process as much as possible. For example, if editing a source code file, the keyboard shortcut would trigger a sequence of actions (generally OpenAI GPT API prompts) on the file's content, providing different kinds of results like Explain Code, Code Readability Review, Code Syntax Correction, Found Bugs, Suggested Improvements, etc. For all those results, the user will then have options like Accept Suggestions, Copy to Clipboard, Save to File, Use as GPT Input,

### Technologies, APIs, and Libraries

- C++17 or later for backend code.
- Qt6 for user interface and network operations.
- QML for dynamic UI design.
- OpenAI's GPT API for code analysis and improvements.
- CMake for build automation.
- Google Test for unit testing (optional).

## Project Structure

```css

Convergence/
│   CMakeLists.txt
│   main.cpp
│   
└───include/
│   │   ApplicationManager.h
│   │   FileHandler.h
│   │   OpenAIApiHandler.h
│   │   Action.h
│   │   ActionManager.h
│   │   ResultsManager.h
│   
└───src/
│   │   ApplicationManager.cpp
│   │   FileHandler.cpp
│   │   OpenAIApiHandler.cpp
│   │   Action.cpp
│   │   ActionManager.cpp
│   │   ResultsManager.cpp
│   
└───qml/
│   │   MainWindow.qml
│   │   CodeEditor.qml
│   │   ActionsPanel.qml
│   │   ResultsPanel.qml
│   
└───tests/ (optional)
    │   ApplicationManagerTest.cpp
    │   FileHandlerTest.cpp
    │   OpenAIApiHandlerTest.cpp
    │   ActionTest.cpp
    │   ActionManagerTest.cpp
    │   ResultsManagerTest.cpp
```

## Design

### Qt/QML Frontend

- Main Window: This would be the primary interface for your application. It will contain the menu, toolbar, and status bar.
- Code Editor: You would have a QTextEdit (or similar) widget where the user can edit their source code. This should have syntax highlighting and other code editor features.
- Actions Panel: This would be a QListWidget (or similar) that contains all the different actions (like "Explain Code", "Code Readability Review", etc.). You can attach these actions to keyboard shortcuts using QShortcut.
- Results Panel: This would be another QListWidget (or similar) that contains the results of the actions. Each result would be a QListWidgetItem with a checkbox next to it.
- Context Menu: This would be a QMenu that pops up when the user right-clicks on a result. It would contain options like "Accept Suggestions", "Copy to Clipboard", etc.

### C++ Backend

- File Management: You would need classes to handle opening, saving, and modifying files. QFile and QTextStream would be useful here.
- OpenAI GPT API Integration: This would involve sending HTTP requests to the OpenAI GPT API and parsing the JSON responses. QNetworkAccessManager and QJsonDocument would be useful here. You would probably want a separate class to handle this, as it could get quite complex.
- Actions: You would need a class for each action. Each action class would have a method that takes a QString (the contents of the code editor) and returns a QList<QVariant> (the results). You would then need a class to manage all these actions, possibly using a QMap<QString, QAction*>.
- Results: You would need a class to manage the results. This would handle checking and unchecking the checkboxes, as well as the context menu actions.

## Main Classes and Relations

- ApplicationManager: This is the main class that initializes and coordinates all the other classes. It interacts with all of them and is responsible for starting and stopping the application.
- FileHandler: This class handles all file operations, such as opening, saving, and modifying files. It is used by ApplicationManager.
- OpenAIApiHandler: This class manages all interactions with the OpenAI GPT API. It sends requests and parses responses. It is used by Action and ActionManager classes.
- Action: This is a base class for all actions. Each specific action ("Explain Code", "Code Readability Review", etc.) would be a subclass of Action.
- ActionManager: This class manages all the actions. It maps keyboard shortcuts to actions and executes the appropriate action when a shortcut is pressed. It uses the Action and OpenAIApiHandler classes.
- ResultsManager: This class manages the results of the actions. It handles checking and unchecking the checkboxes, as well as the context menu actions. It interacts with the ActionsPanel and ResultsPanel classes in QML.
CMakeLists.txt
```
 cmake_minimum_required(VERSION 3.14)
project(Convergence)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH "/usr/local/Qt-6.2.0/lib/cmake")
endif()

find_package(Qt6 COMPONENTS Core Quick REQUIRED)

add_executable(${PROJECT_NAME} 
    main.cpp 
    qml.qrc 
    ApplicationManager.h 
    FileHandler.h 
    OpenAIApiHandler.h 
    Action.h 
    ActionManager.h 
    ResultsManager.h 
    OpenAIAgent.h 
    OpenAIAgent.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Quick)

# Add your source files and directories here
```
ApplicationManager.h

```cpp

#pragma once

#include "FileHandler.h"
#include "ActionManager.h"
#include "ResultsManager.h"

class ApplicationManager
{
public:
    ApplicationManager();
    ~ApplicationManager();

    void startApplication();
    void stopApplication();

private:
    FileHandler fileHandler;
    ActionManager actionManager;
    ResultsManager resultsManager;
};
```
FileHandler.h

```cpp

#pragma once

#include <QString>

class FileHandler
{
public:
    FileHandler();

    QString openFile(const QString& filePath);
    void saveFile(const QString& filePath, const QString& content);
};
```
OpenAIApiHandler.h

```cpp

#pragma once

#include <QString>
#include <QJsonDocument>

class OpenAIApiHandler
{
public:
    OpenAIApiHandler();

    QJsonDocument sendRequest(const QString& codeContent);
};
```
Action.h

```cpp

#pragma once

#include <QString>
#include <QList>
#include <QVariant>
#include "OpenAIApiHandler.h"

class Action
{
public:
    Action();
    virtual ~Action();

    virtual QList<QVariant> performAction(const QString& codeContent, OpenAIApiHandler& apiHandler) = 0;
};
```
ActionManager.h

```cpp

#pragma once

#include <QMap>
#include <QString>
#include "Action.h"

class ActionManager
{
public:
    ActionManager();

    void registerAction(const QString& actionName, Action* action);
    QList<QVariant> executeAction(const QString& actionName, const QString& codeContent);

private:
    QMap<QString, Action*> actionMap;
};
```
ResultsManager.h

```cpp

#pragma once

#include <QList>
#include <QVariant>

class ResultsManager
{
public:
    ResultsManager();

    void displayResults(const QList<QVariant>& results);
    void handleResultSelection(int resultIndex);
};
```
These are the header files for your classes. Each class has a constructor and the necessary methods. The Action class is an abstract base class with a pure virtual method performAction(), which will be implemented by its subclasses.

Please note that the QVariant type is used to represent the results. This is a general-purpose container that can hold various types. You can change this to a specific type if you prefer. The same goes for the parameters of the performAction() and executeAction() methods.
OpenAIApi.h:
```
#ifndef OPENAIAGENT_H
#define OPENAIAGENT_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QProcessEnvironment>
#include <QFile>
#include <QSharedPointer>

class OpenAIApi;
class Agent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName CONSTANT)
    Q_PROPERTY(QString responseText READ getResponse NOTIFY responseReceived)

public:
    // Takes a name and a system message content string as input.
    // Initializes the OpenAIApi instance with the given API key and system message content.
    Agent(const QString& name, const QString& systemMessageContent, QObject* parent = nullptr);

    virtual ~Agent() = default;

    // Returns the name of the agent.
    Q_INVOKABLE QString getName() const { return name; }

    // Returns the responseText which is the response generated by the OpenAI API.
    Q_INVOKABLE QString getResponse() const { return responseText; }

    // Appends the given text to the userMessage to be sent to the OpenAI API. Emits Agent:;userMessageChanged.
    Q_INVOKABLE void appendRequest(const QString& text) {
        userMessage += text;
        emit userMessageChanged(text);
    }

public slots:
    // Sends a request to the OpenAI API with the current userMessage. It delegates the task to the OpenAIApi::sendRequest method.
    void sendRequest();

private slots:
    // Handles the response received from the OpenAI API.
    // Sets the responseText and emits the responseReceived signals.
    void handleResponse(const QString& response);

    // Handles the error received from the OpenAI API.
    // Emits the errorOccurred and updatedChanged signals.
    void handleError(const QString& errorMessage);

signals:
    // Signal is emitted when the response is received from the OpenAI API. It can be connected to QML to update the UI with the new response.
    void responseReceived(const QString& responseText);

    // Signal emitted when an error occurs while processing the API request.
    void errorOccurred(const QString& errorMessage);

    // Signal emitted when the userMessage is changed.
    void userMessageChanged(const QString& newText);

private:
    QString name;
    QString responseText{"No response."};
    QString userMessage{""};
    QSharedPointer<OpenAIApi> apiHelper;
};

class OpenAIApi : public QObject
{
    Q_OBJECT

public:
    // Takes the API key variable name and a system message content string as input.
    OpenAIApi(const QString& apiKeyVariable, const QString& systemMessageContent, QObject* parent = nullptr);

    // Takes the userMessage and sends a request to the OpenAI API using QNetworkAccessManager. When the request is finished, it triggers the OpenAIApi::networkRequestFinished slot.
    void sendRequest(const QString& userMessage);

signals:
    // Signal emitted when a response is received from the OpenAI API. It is connected to the Agent::handleResponse slot.
    void responseReceived(const QString& response);

    // Signal emitted when an error occurs while processing the API request.
    void errorOccurred(const QString& errorMessage);

private slots:
    // Handles the completion of the network request. If the request is successful, it extracts the response and emits the responseReceived signal. If there is an error, it emits the errorOccurred signal.
    void networkRequestFinished(QNetworkReply* reply);

private:
    Q_DISABLE_COPY(OpenAIApi)
    QNetworkAccessManager networkManager;
    QString apiKey;
    QJsonObject systemMessage;
};
#endif
```
OpenAIApi.cpp:
```#include "OpenAIAgent.h"
#include <QProcessEnvironment>
#include <QFile>
//#include <QQmlEngine>

Agent::Agent(const QString& name, const QString& systemMessageContent, QObject* parent)
    : QObject(parent), name(name)
{
    //QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    apiHelper = QSharedPointer<OpenAIApi>::create("OPENAI_API_KEY", systemMessageContent , this);
    connect(apiHelper.data(), &OpenAIApi::responseReceived, this, &Agent::handleResponse);
    connect(apiHelper.data(), &OpenAIApi::errorOccurred, this, &Agent::handleError);
}

void Agent::sendRequest()
{
    apiHelper->sendRequest(userMessage);
}

void Agent::handleResponse(const QString& response)
{
    responseText = response;
    emit responseReceived(response);
}

void Agent::handleError(const QString& errorMessage)
{
    emit errorOccurred(errorMessage);
}

OpenAIApi::OpenAIApi(const QString& apiKeyVariable, const QString& systemMessageContent, QObject* parent)
    : QObject(parent), networkManager(this)
{
    apiKey = QProcessEnvironment::systemEnvironment().value(apiKeyVariable, "");
    if (apiKey.isEmpty()) {
        QFile file("../.env");
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray data = file.readAll();
            file.close();

            QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                apiKey = jsonDoc.object().value(apiKeyVariable).toString();
            } else {
                apiKey = "";
            }
        } else {
            qWarning("Couldn't open file.");
            apiKey = "";
        }
    }

    systemMessage = QJsonObject {
        {"role", "system"},
        {"content", systemMessageContent}
    };

    connect(&networkManager, &QNetworkAccessManager::finished, this, &OpenAIApi::networkRequestFinished);
}

void OpenAIApi::sendRequest(const QString& userMessage)
{
    QNetworkRequest request(QUrl("https://api.openai.com/v1/chat/completions"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(apiKey).toUtf8());

    QJsonArray messages{
        {systemMessage},
        {QJsonObject{ {"role", "user"}, {"content", userMessage}}}
    };
    QJsonObject requestData {
        {"model", "gpt-3.5-turbo"},
        {"messages", messages}
    };

    QByteArray payloadData = QJsonDocument(requestData).toJson(QJsonDocument::Compact);
    QNetworkReply* reply = networkManager.post(request, payloadData);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        networkRequestFinished(reply);
    });
}

void OpenAIApi::networkRequestFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonDocument responseJsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject responseJsonObj = responseJsonDoc.object();
        QJsonValue assistantMessage = responseJsonObj["choices"].toArray()[0].toObject()["message"].toObject()["content"];
        emit responseReceived(QString(assistantMessage.toString()));
    }
    else
    {
        emit errorOccurred(tr("Error: %1 (code: %2)").arg(reply->errorString()).arg(reply->error()));
    }
    reply->deleteLater();
}

```
main.cpp:
```
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFile>
#include <QProcessEnvironment>
#include "OpenAIAgent.h"

QJsonArray loadSystemChatsFromFile(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
        return QJsonArray();
    }

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &error);
    if (error.error != QJsonParseError::NoError) {
        qWarning("Error parsing JSON: %s", qPrintable(error.errorString()));
        return QJsonArray();
    }

    if (!jsonDoc.isArray()) {
        qWarning("JSON document is not an array.");
        return QJsonArray();
    }
    return jsonDoc.array();
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Agent>("com.agents.openai", 1, 0, "Agent");
    
    QJsonArray systemChats = loadSystemChatsFromFile(":/system_chats.json");

    QList<QObject*> agents;
    for (const QJsonValue& systemChatValue : systemChats)
    {
        const QJsonObject systemChatObj = systemChatValue.toObject();
        const QString agentName = systemChatObj.value("name").toString();
        const QJsonArray systemMsgs = systemChatObj.value("msgs").toArray();
        QString systemMessageContent;
        for (const QJsonValue& systemMsg : systemMsgs) {
            const QJsonObject systemMsgObj = systemMsg.toObject();
            if (systemMsgObj.value("role").toString() == "system") {
                systemMessageContent = systemMsgObj.value("content").toString();
                break;
            }
        }
        Agent* agent = new Agent(agentName, systemMessageContent);
        agents.append(agent);
    }

    engine.rootContext()->setContextProperty("agentsList", QVariant::fromValue(agents));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
```
