# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BackEnd\\BackEnd_autogen"
  "BackEnd\\CMakeFiles\\BackEnd_autogen.dir\\AutogenUsed.txt"
  "BackEnd\\CMakeFiles\\BackEnd_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\appWeatherApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appWeatherApp_autogen.dir\\ParseCache.txt"
  "appWeatherApp_autogen"
  "common\\CMakeFiles\\common_autogen.dir\\AutogenUsed.txt"
  "common\\CMakeFiles\\common_autogen.dir\\ParseCache.txt"
  "common\\common_autogen"
  )
endif()
