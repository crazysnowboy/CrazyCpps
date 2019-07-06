

function(GobalInit global_variable new_datas)
    SET_PROPERTY(GLOBAL PROPERTY global_variable "")
endfunction()


function(ReadGlobal global_variable out_data)
    GET_PROPERTY(read_data GLOBAL PROPERTY ${global_variable})
    set(${out_data} ${read_data} PARENT_SCOPE)
endfunction()




function(Gobal_Append global_variable new_datas)

    separate_arguments(new_datas)

    foreach(data  ${new_datas})
        list(APPEND new_data_list ${data})
    endforeach()

    GET_PROPERTY(read_data GLOBAL PROPERTY ${global_variable})
    SET_PROPERTY(GLOBAL PROPERTY ${global_variable} "${read_data} ${new_data_list}")

endfunction()





#execute_process(COMMAND cmake --help-property-list OUTPUT_VARIABLE CMAKE_PROPERTY_LIST)
#STRING(REGEX REPLACE ";" "\\\\;" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
#STRING(REGEX REPLACE "\n" ";" CMAKE_PROPERTY_LIST "${CMAKE_PROPERTY_LIST}")
#message ("CMAKE_PROPERTY_LIST = ${CMAKE_PROPERTY_LIST}")
