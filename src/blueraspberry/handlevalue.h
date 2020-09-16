#ifndef _HANDLEVAL_H
#define _HANDLEVAL_H

#include <vector>
#include <iostream>
#include <string>

#include "blueraspberry.h"

BR::Object* handlevalue(BR::Object* val, BR::Context context, std::vector<std::string> stack);
BR::Object* handlefcall(BR::Statements::FunctionCall *call, BR::Context context, std::vector<std::string> stack);
BR::Object* handlecall(BR::Function *call, BR::Array args, BR::Context context, std::vector<std::string> stack);
std::vector<BR::Object*> handlearray(std::vector<BR::Object*> arr, BR::Context context, std::vector<std::string> stack);

BR::Object* handlevalue(BR::Object* val, BR::Context context, std::vector<std::string> stack) {
    if (BR::VariableReference *value = dynamic_cast<BR::VariableReference*>(val))
        return context.get(value->value);
    else if (BR::Array *item = dynamic_cast<BR::Array*>(val))
        return new BR::Array(handlearray(item->data, context, stack));
    else if (BR::Undefined *item = dynamic_cast<BR::Undefined*>(val))
        return new BR::Undefined();
    else if (BR::Statements::FunctionCall *item = dynamic_cast<BR::Statements::FunctionCall*>(val)) {
        return handlefcall(item, context, stack);
    } else
        return val;
}

BR::Object* handlefcall(BR::Statements::FunctionCall *call, BR::Context context, std::vector<std::string> stack) {
    if (BR::Undefined *contextItem = dynamic_cast<BR::Undefined*>(context.get(call->funcname))) {
        error("(Failed) attempt to call 'undefined'.", stack);
    } else {
        if (BR::Function *func = dynamic_cast<BR::Function*>(context.get(call->funcname))) {
            BR::Array args = BR::Array(handlearray(call->arglist.data, context, stack));
            return handlevalue(func->callback(context, args), context, stack);                    
        } else
            error("(Failed) attempt to call a value that isn't a function.", stack);
    }
}

BR::Object* handlecall(BR::Function *call, BR::Array args, BR::Context context, std::vector<std::string> stack) {
    BR::Array argl = BR::Array(handlearray(args.data, context, stack));
    return handlevalue(call->callback(context, argl), context, stack); 
}

std::vector<BR::Object*> handlearray(std::vector<BR::Object*> arr, BR::Context context, std::vector<std::string> stack) {
    std::vector<BR::Object*> output = std::vector<BR::Object*>();

    for (int i = 0; i < arr.size(); i++) {
        BR::Object *obj = arr[i];
        output.push_back(handlevalue(obj, context, stack));
    }

    return output;
}

#endif