{
    'targets': [
    {
        'target_name': 'napi_sdl2',
        'sources': [
            'src/napi_sdl2.c',
        ],
        'conditions': [
            ['OS=="linux"', {
                'libraries': [
                    '-lSDL2',
                    '-lSDL2_ttf',
                ],
                'include_dirs': [
                    '-I/usr/include/SDL2',
                ],
                'defines': [
                    '_REENTRANT'
                ]
            }],
        ],
        'defines': [
            '_THREAD_SAFE',
            'ENABLE_ARG_CHECKING',
        ]
    }
    ]
}
