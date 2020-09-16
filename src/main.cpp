#include <iostream>
#include <vector>
#include <string>

#include "b1.h"
#include "b1-inbuilts.h"

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string path = argv[1];

        std::string module_path = modulePath(path);
        std::string module = loadModule(module_path);

        B1::Context context = B1::Context();

        context = add_inbuilts(context, module_path);

        B1::Script scr = B1::Script(module, context, module_path);
        scr.Run();
    } else
        std::cout << "Usage: blueraspberry <string>" << std::endl;

    return 0;
}