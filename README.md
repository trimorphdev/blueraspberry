<p align="center">
    <img src="assets/logo.svg" width="40%">
</p>

## What is Blue Raspberry?
Blue Raspberry is a hobby programming language inspired by multiple programming languages, but most strongly influenced by JavaScript/TypeScript and PHP.

## Building
To get started with Blue Raspberry, you're going to have to build it from scratch (unless I decide to publish prebuild binaries, which probably won't happen in the immediate future).  Luckily, I've made a build script to simplify the process of building the project.  Unfortunately, using this build script does require Node.js, but I'm sure it would be easy to make a build script in a different programming language if you positively need to make a different build script.

```sh
# Install Dependencies
npm install

# Run build script
node build
```

Now if you want to test if it has built correctly, you can run the following command:

```sh
# Windows
bin\blueraspberry tests\main

# MacOS, Linux or pretty much anything that isn't Windows
bin/blueraspberry tests/main
```

## Blue Raspberry VM
If you've copied the files from the `include` folder to your compiler's include path, you should now have access to Blue Raspberry's API, here's an example:

```c++
#include <b1.h>

void main() {
    B1::Context context = B1::Context();
    B1::Script scr = B1::Script("var x = 'test'", context, "filepath");

    // Run the script:
    scr.run();
}
```