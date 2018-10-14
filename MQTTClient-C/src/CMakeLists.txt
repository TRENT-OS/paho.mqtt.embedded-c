# MQTTClient Library - C

file(GLOB SOURCES "*.c" "seL4/*.c")

add_library(
  paho-embed-mqtt3cc STATIC
  ${SOURCES}
)

target_compile_definitions(paho-embed-mqtt3cc PRIVATE
             MQTTCLIENT_PLATFORM_HEADER=MQTTseL4.h MQTTCLIENT_QOS2=1)

target_include_directories(paho-embed-mqtt3cc PUBLIC seL4)
target_include_directories(paho-embed-mqtt3cc PUBLIC .)

target_link_libraries( paho-embed-mqtt3cc muslc )
