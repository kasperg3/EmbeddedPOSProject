project(shp_queue)

set(source_files
 	queue.cpp
  	queue.h
  	)

add_library(shp_queue STATIC ${source_files})

#target_link_libraries(shp_queue rt)