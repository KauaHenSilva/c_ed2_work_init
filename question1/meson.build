project(
  'Question1',
  'c',
  version : '0.1',
  default_options : ['warning_level=3'],
)

subdir('src')

executable(
  'main',
  'src/main.c',
  link_with: libs,
  include_directories: incs,
  install : true,
)
