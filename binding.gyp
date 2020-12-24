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
            ['OS=="mac"', {
                'libraries': [
                    '/usr/local/lib/libSDL2.dylib',
                ],
                'xcode_settings': {
                    'OTHER_LDFLAGS': [
                          '-undefined dynamic_lookup',
                          '-framework Cocoa',
                          '-framework OpenGL',
                          '-framework OpenAL',
                    ]
                },
                'include_dirs': [
                    '/usr/local/include/SDL2',
                    '/usr/local/include'
                ]
            }]
        ],
        'defines': [
            '_THREAD_SAFE',
            'ENABLE_ARG_CHECKING',
        ]
    }
    ]
}
