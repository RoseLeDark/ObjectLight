#pragma once 

#include "uuid.h"
#include "Object.h"
#include <string>
#include "Function.h"

namespace OB {

    #define MovebleObjectUUID "019c3f3c-dfaa-76a3-bc7c-5ef824256f44"
    class OBL_API MovebleObject : public Object {
    public:
        using type = MovebleObject;
        using this_type = MovebleObject;
        using base_type = Object;

        explicit MovebleObject(uuid SubUUID) 
            : base_type(MovebleObjectUUID, SubUUID, "MovebleObject") { }

        virtual uint8_t move(Object sender, uint64_t timestamp) = 0;
    };

    #define PrintebleObjectUUID "019c3f3c-dfaa-7e98-818c-590db3522b5b"
    class OBL_API PrintebleObject : public Object {
    public:
        using type = PrintebleObject;
        using this_type = PrintebleObject;
        using base_type = Object;

        explicit PrintebleObject(uuid SubUUID) 
            : base_type(PrintebleObjectUUID, SubUUID, "PrintebleObject") { }

        virtual void print(std::ostream stream) = 0;
    };

    #define VisualObjectUUID "019c3f3c-dfaa-72eb-8118-d306f9b255bc"
    class OBL_API VisualObject : public Object {
    public:
        using type = VisualObject;
        using this_type = VisualObject;
        using base_type = Object;

        explicit VisualObject(uuid SubUUID) 
            : base_type(VisualObjectUUID, SubUUID, "VisualObject") { }

        virtual uint8_t move(Object sender, uint64_t timestamp) = 0;
        virtual uint8_t draw(Object sender, uint8_t drawOrder, const char* techniqueName) = 0;
    };

    #define StringObjectUUID "0c6cf68c-b832-4282-a79e-c5b016924dac"
    class OBL_API StringObject : public Object {
    public:
        using type = StringObject;
        using this_type = StringObject;
        using base_type = Object;

		explicit StringObject(std::string str, uuid SubUUID) 
            : base_type(StringObjectUUID, SubUUID, "StringObject"), m_strString(str) { }

        virtual std::string get() { return m_strString; }
        virtual void set(std::string str) { m_strString = str; }
    protected:
        std::string m_strString;
    };

    #define ValueObjectUUID     "019c3f3c-dfaa-77b4-af1a-59811116666c"
    class  ValueObject : public Object {
    public:
        using type = ValueObject;
        using this_type = ValueObject;
        using base_type = Object;

		explicit ValueObject(uint32_t value, uuid SubUUID) 
            : base_type(ValueObjectUUID, SubUUID, "ValueObject"), m_ValueType(value) { }

        virtual uint32_t get() { return m_ValueType; }
        virtual void set(uint32_t str) { m_ValueType = str; }
    protected:
        uint32_t m_ValueType;
    };

    #define FloatObjectUUID     "019c3f3c-dfaa-7e98-818c-590db3522b5b"
    class  FloatObject : public Object {
    public:
        using type = FloatObject;
        using this_type = FloatObject;
        using base_type = Object;

		explicit FloatObject(float value, uuid SubUUID) 
            : base_type(FloatObjectUUID, SubUUID, "FloatObject"), m_ValueType(value) { }

        virtual float get() { return m_ValueType; }
        virtual void set(float str) { m_ValueType = str; }
    protected:
        float m_ValueType;
    };

    #define MessengerObjectUUID     "019c3f44-4e50-71d8-b538-47d03f45ce21"
    class  MessengerObject : public Object {
    public:
        using type = MessengerObject;
        using this_type = MessengerObject;
        using base_type = Object;

		explicit MessengerObject(uuid SubUUID) 
            : base_type(MessengerObjectUUID, SubUUID, "MessengerObject") { }

        virtual int OnMessage(Object sender, uint16_t messageID) = 0;
    };
}