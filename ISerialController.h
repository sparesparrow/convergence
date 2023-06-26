
class Serial 
{
public:
    Serial() = default;
    Serial(const char* data, int32_t size):data(data), mysize(size) {}
    Serial(const Serial& obj) { data = obj.data; mysize = obj.mysize; }
    const Serial& operator=(const Serial& obj)
    {
        if (this != &obj)
        {
            data = obj.data;
            mysize = obj.mysize;
        }
        return *this;
    }
    virtual ~Serial() = default;
    virtual int32_t size() { return mysize; }
    virtual const char* getData() const { return data; }
    virtual void setData(const char* data_, int32_t size_)
    {
        mysize = size_;
        data = data_;
    }
    std::vector<int8_t> vector()
    {
        return std::vector<int8_t>(data, data + mysize);
    }
private:
    const char* data{nullptr};
    int32_t mysize{0};
};

class ISerialWriter
{
public:
   virtual ~ISerialWriter() = default;
   virtual void write(const Serial& data) = 0;
};

class ISerialReader
{
public:
   virtual ~ISerialReader() = default;
   virtual Serial read() = 0;
};

class IController {
public:
   virtual ~IController() = default;
   virtual void send(ISerialWriter& writer) = 0;
   virtual ISerialReader& recv() = 0;
};

class Controller : public IController {
public:
   Controller(ISerialWriter& writer, ISerialReader& reader) : writer(writer), reader(reader) {}
   virtual ~Controller() = default;
   virtual void send(ISerial& serial) override {
       writer.write(serial.read());
   }
   virtual ISerial& recv() override {
       return reader;
   }
private:
   ISerialWriter& writer;
   ISerialReader& reader;
};

class FbBuilder
{
public:
    FbBuilder(): builder(16 * 1024) { builder.ForceDefaults(true); }
    virtual ~FbBuilder() = default;
    char* serialData;
    int32_t serialSize;
protected:
    flatbuffers::FlatBufferBuilder builder;
};

template<typename T>
const T* readReq(Serial msg)
{
    if (msg.size() <= 0)
    {
        return nullptr;
    }
    flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t*>(msg.getData()), msg.size());
    auto req = flatbuffers::GetRoot<T>(msg.getData());
    if (!req->Verify(verifier))
    {
        return nullptr;
    }
    return req;
};

bool RequestReader::read(Serial msg)
{
    if (msg.size() <= 0)
    {
        return false;
    }
    flatbuffers::Verifier verifier(reinterpret_cast<const uint8_t*>(msg.getData()), msg.size());
    req = flatbuffers::GetRoot<MsgDataTypes::Request>(msg.getData());
    return req->Verify(verifier);
}

MsgDataTypes::MessageType RequestReader::getType() const
{
    return static_cast<MsgDataTypes::MessageType>(req->data_type());
}

Serial ResponseWriter::write()
{
    builder.Clear();
    return finish(MsgDataTypes::CreateTestInfoResponse(builder, data).Union(), MsgDataTypes::ResponsePayload_TestInfoResponse);
}

Serial ResponseWriter::finish(flatbuffers::Offset<void> data, MsgDataTypes::MessageType type)
{
    Serial output;
    flatbuffers::Offset<MsgDataTypes::Response> message = MsgDataTypes::CreateResponse(builder, type, data);
    builder.Finish(message);
    output.setData(reinterpret_cast<const char*>(builder.GetBufferPointer()), builder.GetSize());
    return output;
}
