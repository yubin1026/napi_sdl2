
import { createRequire } from 'module';
const require = createRequire(import.meta.url);

const napi_sdl2 = require('./build/Release/napi_sdl2.node');

export default napi_sdl2;

