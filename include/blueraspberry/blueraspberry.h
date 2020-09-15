#ifndef _BR_H
#define _BR_H

#include <string>
#include <unordered_map>
#include <iostream>

#include "error.h"

namespace BR {
    class Object {
    public:
        bool constant = false;

        virtual ~Object() {};
    };

    class Null : public Object {};

    class Undefined : public Object {};

    class Bool : public Object {
    public:
        bool value;

        Bool(bool value) {
            this->value = value;
        }
    };

    class String : public Object {
    public:
        std::string value;

        String(std::string value) {
            this->value = value;
        }
    };

    class Int : public Object {
    public:
        int value;

        Int(int value) {
            this->value = value;
        }
    };

    class Float : public Object {
    public:
        float value;

        Float(float value) {
            this->value = value;
        }
    };

    class VariableReference : public Object {
    public:
        std::string value;

        VariableReference(std::string name) {
            this->value = name;
        }
    };

    namespace Statements {
        class Import : public Object {
        public:
            std::string module;
            
            Import(std::string name) {
                this->module = name;
            }
        };

        class VariableDefinition : public Object {
        public:
            std::string varname;
            Object *value;
            
            VariableDefinition(std::string name, Object *value) {
                this->varname = name;
                this->value = value;
            }
        };

        class VariableSet : public Object {
        public:
            std::string varname;
            Object *value;
            
            VariableSet(std::string name, Object *value) {
                this->varname = name;
                this->value = value;
            }
        };
    }

    class Context {
    public:
        std::unordered_map<std::string, Object*> data;

        Context() {}
        Context(std::unordered_map<std::string, Object*> data) {
            this->data.insert(data.begin(), data.end());
        }

        Context Clone() {
            return Context(this->data);
        }

        Object* get(std::string key) {
            auto iter = this->data.find(key);
            
            if (iter == this->data.end())
                return new Undefined();
            else
                return iter->second;
        }

        void set(std::string key, Object *value) {
             auto iter = this->data.find(key);

            if (iter == this->data.end())
                this->data.insert({key, value});
            else
                iter->second = value;
        }

        void merge(Context context) {
           this->data.insert(context.data.begin(), context.data.end());
        }

        void log() {
            for (auto iter : this->data)
                std::cout << iter.first << " ";
            std::cout << std::endl;
        }
    };
}

#endif