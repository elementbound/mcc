project('macrocol', 'c',
    default_options: [
        'c_std=c11'
    ])

includes = include_directories('include')
sources = [ 'src/macrocol/typehandlers.c', 'src/macrocol/vector.c', 'src/macrocol/treeset.c', 'src/macrocol/treemap.c', 'src/macrocol/hashset.c' ]

library('mcc', sources, include_directories: includes)

executable('vector-sample', 'src/samples/vector-sample.c', sources, include_directories: includes)
executable('treeset-sample', 'src/samples/treeset-sample.c', sources, include_directories: includes)
executable('treeset-strings', 'src/samples/treeset-strings.c', sources, include_directories: includes)
executable('treemap-sample', 'src/samples/treemap-sample.c', sources, include_directories: includes)
executable('hashset-sample', 'src/samples/hashset-sample.c', sources, include_directories: includes)

executable('bsearch_visual', 'src/samples/bsearch_visual.c')

# Doxygen
doxygen = find_program('doxygen', required : false)
if doxygen.found()
  message('Doxygen found')
  run_target('docs', command : [doxygen, meson.source_root() + '/Doxyfile'])    
else
  warning('Documentation disabled without doxygen')
endif

custom_target('docs',
    command: [doxygen, meson.source_root() + '/Doxyfile'],
    output: '.',
    install: false,
    build_by_default: true
)
