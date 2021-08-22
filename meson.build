project('macrocol', 'c',
    default_options: [
        'c_std=c11'
    ])

includes = include_directories('include')
sources = [ 'src/macrocol/vector.c', 'src/macrocol/treeset.c', 'src/macrocol/treemap.c' ]

executable('vector-sample', 'src/samples/vector-sample.c', sources, include_directories: includes)
executable('treeset-sample', 'src/samples/treeset-sample.c', sources, include_directories: includes)
executable('treemap-sample', 'src/samples/treemap-sample.c', sources, include_directories: includes)