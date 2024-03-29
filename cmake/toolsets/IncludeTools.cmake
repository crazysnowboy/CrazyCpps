

function(MyIncludeRecursive include_dirs out_inc_dirs)
    foreach(curdir ${include_dirs})
        if(IS_DIRECTORY ${curdir})
            set(dirs_lists  ${dirs_lists} ${curdir})
            FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
            foreach(child ${children})
                if(IS_DIRECTORY ${curdir}/${child})
                    MyIncludeRecursive(${curdir}/${child} dirs_lists)
                endif()
            endforeach()
        endif()
    endforeach()
    set(${out_inc_dirs} ${dirs_lists} PARENT_SCOPE)
endfunction(MyIncludeRecursive)

function(MyInclude include_dirs out_inc_dirs)
    foreach(curdir  ${include_dirs})
        set(dirs_lists  ${dirs_lists} ${curdir})
        FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
        foreach(child ${children})
            if(IS_DIRECTORY ${curdir}/${child})
                set(dirs_lists  ${dirs_lists} ${curdir}/${child})
            endif()
        endforeach()
    endforeach()
    set(${out_inc_dirs} ${${out_inc_dirs}}  ${dirs_lists} PARENT_SCOPE)
endfunction(MyInclude)
