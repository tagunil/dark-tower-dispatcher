import qbs

Project {
    minimumQbsVersion: "1.7.1"

    CppApplication {
        consoleApplication: true
        files: [
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
            "main.cpp",
        ]

        Group {
            fileTagsFilter: product.type
            qbs.install: true
        }
    }
}
