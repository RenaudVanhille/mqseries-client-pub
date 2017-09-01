{
  "targets": [
    {
      "include_dirs": [
        "./",
        "/opt/mqm/inc/"
      ],
      "libraries": [
        "-L/opt/mqm/lib64",
        "-lmqm"
      ],
      "target_name": "mq_pub",
      "main": "./build/Release/mq_pub.node",
      "sources": [
        "main.cc",
        "Pub/CPub.cpp",
        "Promise/CPromiseData.cpp"
      ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "cflags": [ "-fPIC", "-std=c++14", "-pedantic", "-fexceptions", "-Wall" ],
      "cflags_cc": [ "-fPIC", "-std=c++14", "-pedantic", "-fexceptions", "-Wall" ],
    },
  ],
}