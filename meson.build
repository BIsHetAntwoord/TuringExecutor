project(
    'TuringExecutor',
    ['cpp'],
    version: '0.0.0',
    default_options: [
        'cpp_std=c++2a',
        'buildtype=debug',
    ]
)

# Final executable
sources = [
    'src/executor.cpp',
    'src/main.cpp',
    'src/parser.cpp',
    'src/tape.cpp'
]

executable(
    'turingexec',
    [sources],
    install: true,
    build_by_default: true,
    include_directories: [include_directories('include')],
)