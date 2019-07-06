
function(delete files_paths)
    file(GLOB_RECURSE delete_files  ${files_paths})
    foreach(delete_file ${delete_files})
        file(REMOVE  ${delete_file})
    endforeach(delete_file)
endfunction(delete)


function(RemoveFiles RemoveSRCINC_DIR RemoveModule_DIR RemoveFileType)

    separate_arguments(RemoveSRCINC_DIR)
    separate_arguments(RemoveModule_DIR)
    separate_arguments(RemoveFileType)
    foreach(curdir_inc_src ${RemoveSRCINC_DIR})
        foreach(curdir ${RemoveModule_DIR})
            foreach(type ${RemoveFileType})
                delete("${curdir_inc_src}/${curdir}/${type}")
#                message("-----remomve in ${curdir_inc_src}/${curdir}/${type}---------")
            endforeach()
        endforeach()
    endforeach()

endfunction()



