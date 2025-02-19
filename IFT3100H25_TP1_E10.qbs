import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "ThirdParty/of_v0.12.0_linux64gcc6_release/libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: "ThirdParty/of_v0.12.0_linux64gcc6_release"

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            'src/Canvas.cpp',
            'src/Canvas.hpp',
            'src/Controller.hpp',
            'src/Controller2D.cpp',
            'src/Controller2D.hpp',
            'src/DrawingTools.cpp',
            'src/DrawingTools.hpp',
            'src/Node2D.cpp',
            'src/Node2D.hpp',
            'src/app/Application.cpp',
            'src/app/Application.hpp',
            'src/app/Renderer.cpp',
            'src/app/Renderer.hpp',
            'src/main.cpp',
            'src/ofApp.cpp',
            'src/ofApp.h',
            'src/plugin/image/Exporting.hpp',
            'src/plugin/image/Histogram.cpp',
            'src/plugin/image/Histogram.hpp',
            'src/plugin/image/Importing.hpp',
            'src/plugin/image/Sampling.hpp',
            'src/plugin/image/image.hpp',
            'src/plugin/primitive/Line2D.cpp',
            'src/plugin/primitive/Line2D.hpp',
            'src/plugin/primitive/Point2D.cpp',
            'src/plugin/primitive/Point2D.hpp',
            'src/plugin/primitive/Primitive2D.cpp',
            'src/plugin/primitive/Primitive2D.hpp',
            'src/plugin/primitive/primitive.hpp',
            'src/plugin/states/DrawLineState.cpp',
            'src/plugin/states/DrawLineState.hpp',
            'src/plugin/states/DrawPointState.cpp',
            'src/plugin/states/DrawPointState.hpp',
            'src/plugin/states/State.hpp',
            'src/plugin/states/StateMachine.cpp',
            'src/plugin/states/StateMachine.hpp',
            'src/plugin/states/states.hpp',
        ]

        of.addons: [
            'ofxAssimpModelLoader',
            'ofxGui',
            'ofxImGui',
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
                                // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
                                // will compile OF only once for all your projects
                                // otherwise compiled per project with qbs

    property bool precompileOfMain: false  // precompile ofMain.h
                                           // faster to recompile when including ofMain.h
                                           // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
