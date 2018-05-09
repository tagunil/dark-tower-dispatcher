import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        consoleApplication: true
        files: [
            "bsp.h",
            "character.cpp",
            "character.h",
            "charactertable.cpp",
            "charactertable.h",
            "csvtable.cpp",
            "csvtable.h",
            "dispatcher.cpp",
            "dispatcher.h",
            "emotiontable.cpp",
            "emotiontable.h",
            "influencetable.cpp",
            "influencetable.h",
            "kaCounter.cpp",
            "kaCounter.h",
            "kaTet.cpp",
            "kaTet.h",
            "localcharacter.h",
            "main.cpp",
            "player.cpp",
            "player.h",
            "qhsm.c",
            "qhsm.h",
            "qpc.h",
            "reasons.h",
            "ringbuffer.h",
            "screen.cpp",
            "screen.h",
            "signals.h",
            "stubs.cpp",
        ]

        Group {
            fileTagsFilter: product.type
            qbs.install: true
        }
    }
}
