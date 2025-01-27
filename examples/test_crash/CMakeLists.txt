include_directories(${CMAKE_SOURCE_DIR}/exporters/jaeger/include)

#add_library(opentelemetry_common SHARED IMPORTED)
#set_target_properties(opentelemetry_common PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_common.a")
#add_library(opentelemetry_exporter_jaeger_trace SHARED IMPORTED)
#set_target_properties(opentelemetry_exporter_jaeger_trace PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_exporter_jaeger_trace.a")
#add_library(opentelemetry_http_client_curl SHARED IMPORTED)
#set_target_properties(opentelemetry_http_client_curl PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_http_client_curl.a")
#add_library(opentelemetry_resources SHARED IMPORTED)
#set_target_properties(opentelemetry_resources PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_resources.a")
#add_library(opentelemetry_trace SHARED IMPORTED)
#set_target_properties(opentelemetry_trace PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_trace.a")

#Not needed
#add_library(opentelemetry_exporter_ostream_metrics SHARED IMPORTED)
#set_target_properties(opentelemetry_exporter_ostream_metrics PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_exporter_ostream_metrics.a")
#add_library(opentelemetry_exporter_ostream_span SHARED IMPORTED)
#set_target_properties(opentelemetry_exporter_ostream_span PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_exporter_ostream_span.a")
#add_library(opentelemetry_metrics SHARED IMPORTED)
#set_target_properties(opentelemetry_metrics PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_metrics.a")
#add_library(opentelemetry_version SHARED IMPORTED)
#set_target_properties(opentelemetry_version PROPERTIES IMPORTED_LOCATION "/root/install/lib64/libopentelemetry_version.a")

add_executable(test main.cc)
target_link_libraries(test ${CMAKE_THREAD_LIBS_INIT}
  	opentelemetry_trace 
  	opentelemetry_resources
  	opentelemetry_common
	opentelemetry_exporter_jaeger_trace
	opentelemetry_http_client_curl
	thrift
	curl
	tcmalloc
)
