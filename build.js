const childProcess = require('child_process'),
      glob = require('glob'),
      fs = require('fs'),
      path = require('path');

let files = glob.sync('src/**/*.cpp' , {
    cwd: process.cwd()
});
let compiled = [];

process.on('exit', () => {
    let cleanupFiles = glob.sync('**/*.o' , {
        cwd: process.cwd()
    });
    cleanupFiles.forEach(file => {
        fs.unlinkSync(path.join(process.cwd(), file));
    })
}); 

let error;
files.forEach(function(file, i) {
    if (!error) {
        console.log(`(${i + 1}/${files.length}): ${file}`);
        let child = childProcess.spawnSync('g++', ['--std=c++17', '-pthread', '-c', path.join(process.cwd(), file), '-o', path.join(process.cwd(), path.basename(file, '.cpp') + '.o')])
        let output = child.output.join('');
        if (output.trim() !== '')
            console.log(output);

        if (child.status !== 0)
            error = true;
        
        if (!error)
            compiled.push(path.join(process.cwd(), path.basename(file, '.cpp') + '.o'));
    }
});

if (error)
    process.exit(1);

console.log("Building executable...");
let child = childProcess.spawnSync('g++', ['-o', 'bin/blueraspberry.exe'].concat(compiled));
if (child.output.join('').trim() !== '')
    console.log(child.output.toString())

if (child.status !== 0)
    process.exit(1);