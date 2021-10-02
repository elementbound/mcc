project('mcc', 'c',
    default_options: [
        'c_std=c11'
    ],
    version: '0.7.0')

includes = include_directories('include')
sources = [
    'src/mcc/typehandlers.c',
    'src/mcc/vector.c',
    'src/mcc/treeset.c',
    'src/mcc/treemap.c',
    'src/mcc/hashset.c',
    'src/mcc/hashmap.c'
    ]

library('mcc', sources, include_directories: includes)

executable('vector-sample', 'src/samples/vector-sample.c', sources, include_directories: includes)
executable('treeset-sample', 'src/samples/treeset-sample.c', sources, include_directories: includes)
executable('treeset-strings', 'src/samples/treeset-strings.c', sources, include_directories: includes)
executable('treemap-sample', 'src/samples/treemap-sample.c', sources, include_directories: includes)
executable('hashset-sample', 'src/samples/hashset-sample.c', sources, include_directories: includes)
executable('hashmap-sample', 'src/samples/hashmap-sample.c', sources, include_directories: includes)

executable('bsearch_visual', 'src/samples/bsearch_visual.c')

# Doxygen
doc_config = configuration_data()
doc_config.set('PROJECT_NAME', meson.project_name())
doc_config.set('PROJECT_VERSION', meson.project_version())
doc_config.set('builddir', meson.current_build_dir())
doc_config.set('sourcedir', meson.current_source_dir())

doxyfile = configure_file(input: 'Doxyfile.in',
    output: 'Doxyfile',
    configuration: doc_config,
    install: false)
    
doxygen = find_program('doxygen', required : false)
if doxygen.found()
    custom_target('docs',
        command: [doxygen, doxyfile],
        output: 'docs',
        install: false,
        build_by_default: true,
        build_always_stale: true
    )
else
  warning('Documentation disabled without doxygen')
endif
