#pragma once


#define SAFE_DELETE(d) { if (d) delete d; d = nullptr; }
#define SAFE_DELETE_ARRAY(d) { if (d) delete[] d; d = nullptr; }
