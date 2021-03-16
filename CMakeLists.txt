cmake_minimum_required(VERSION 3.0)
project(n4d-qt-agent)

add_subdirectory(src)
add_subdirectory(qml)

add_custom_target(
    po
    COMMAND xgettext -kde -ki18nd:2 ${CMAKE_CURRENT_SOURCE_DIR}/qml/*.qml ${CMAKE_CURRENT_SOURCE_DIR}/qml/*.cpp -o ${CMAKE_CURRENT_SOURCE_DIR}/messages.po
    COMMENT "extracting po..." 
)

set(langs es ca@valencia)
find_package(Intl)
find_package(Gettext)

foreach(lang ${langs})
    gettext_process_po_files(${lang} ALL PO_FILES locale/${lang}.po)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${lang}.gmo DESTINATION
            share/locale/${lang}/LC_MESSAGES/ RENAME n4d-qt-agent.mo)
endforeach()
