cmake_minimum_required(VERSION 3.0)

project(surgeos 
  VERSION 0.1.1
  LANGUAGES C ASM_NASM)

# Directory setup
set(SURGEOS_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(SURGEOS_IMAGES_DIR ${CMAKE_BINARY_DIR}/images)

file(MAKE_DIRECTORY ${SURGEOS_BINARY_DIR})
file(MAKE_DIRECTORY ${SURGEOS_IMAGES_DIR})

# Subdirectories
add_subdirectory(kernel)
add_subdirectory(libk)

# ELF executable
add_executable(surgeos.elf
  $<TARGET_OBJECTS:surgeos_kernel>
  $<TARGET_OBJECTS:surgeos_libk>
)
target_link_options(surgeos.elf PRIVATE
  -T ${CMAKE_SOURCE_DIR}/linker.ld
)

# Grub setup
set(SURGEOS_GRUB_MENU_LST ${CMAKE_SOURCE_DIR}/grub_config/menu.lst)
set(SURGEOS_IMAGE_NAME "surgeos.img")
set(SURGEOS_IMAGE_PATH "${SURGEOS_IMAGES_DIR}/${SURGEOS_IMAGE_NAME}")
set(SURGEOS_IMAGE_SIZE 100) # MB

set(SURGEOS_KERNEL_TARGET_PATH $<TARGET_FILE:surgeos.elf>)

add_custom_target(
  create_os_image ALL
  COMMAND ${CMAKE_COMMAND} -E make_directory ${SURGEOS_IMAGES_DIR}
  COMMAND ${CMAKE_SOURCE_DIR}/create_image.sh
    ${SURGEOS_IMAGE_PATH}
    ${SURGEOS_IMAGE_SIZE}
    ${SURGEOS_KERNEL_TARGET_PATH}
    ${SURGEOS_GRUB_MENU_LST}
  DEPENDS
    ${SURGEOS_KERNEL_TARGET_PATH}
    ${SURGEOS_GRUB_MENU_LST}
    ${CMAKE_SOURCE_DIR}/create_image.sh
  COMMENT "Creating bootable OS image: ${SURGEOS_IMAGE_PATH}"
)
add_dependencies(create_os_image surgeos_kernel)





