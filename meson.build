project('macrocol', 'c',
    default_options: [
        'c_std=c11'
    ])

includes = include_directories('include')
sources = [ 'src/macrocol/vector.c', 'src/macrocol/treeset.c', 'src/macrocol/treemap.c' ]

library('mcc', sources, include_directories: includes)

executable('vector-sample', 'src/samples/vector-sample.c', sources, include_directories: includes)
executable('treeset-sample', 'src/samples/treeset-sample.c', sources, include_directories: includes)
executable('treeset-strings', 'src/samples/treeset-strings.c', sources, include_directories: includes)
executable('treemap-sample', 'src/samples/treemap-sample.c', sources, include_directories: includes)

executable('bsearch_visual', 'src/samples/bsearch_visual.c')
