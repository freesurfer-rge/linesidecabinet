set(srcs)

list(APPEND srcs pca9685.cpp)
list(APPEND srcs pca9685channel.cpp)

list(APPEND srcs boparraysiposr.cpp)
list(APPEND srcs directdrivesiposhiftregister.cpp)

list(APPEND srcs directdrivesn74x595data.cpp)
list(APPEND srcs directdrivesn74x595.cpp)
list(APPEND srcs boparray595.cpp)

list(APPEND srcs directdrivesn74x164data.cpp)
list(APPEND srcs directdrivesn74x164.cpp)
list(APPEND srcs boparray164.cpp)

target_sources(tendril PRIVATE ${srcs})
