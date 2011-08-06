
#ifndef APP_GL_H
#define APP_GL_H


/*============================================================================================================================================================*/
/*                                                                                                                                                           * /
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5       * /
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#include <toolkits/app/application.h>


#ifdef __cplusplus
extern "C" {
#endif


#ifndef GL_VERSION_1_1
  #define GL_VERSION_1_1 1
  #define APP_GL_VERSION_1_1_DEFINED

  #define GL_ACCUM                                                             0x0100
  #define GL_LOAD                                                              0x0101
  #define GL_RETURN                                                            0x0102
  #define GL_MULT                                                              0x0103
  #define GL_ADD                                                               0x0104
  #define GL_NEVER                                                             0x0200
  #define GL_LESS                                                              0x0201
  #define GL_EQUAL                                                             0x0202
  #define GL_LEQUAL                                                            0x0203
  #define GL_GREATER                                                           0x0204
  #define GL_NOTEQUAL                                                          0x0205
  #define GL_GEQUAL                                                            0x0206
  #define GL_ALWAYS                                                            0x0207
  #define GL_CURRENT_BIT                                                       0x00000001
  #define GL_POINT_BIT                                                         0x00000002
  #define GL_LINE_BIT                                                          0x00000004
  #define GL_POLYGON_BIT                                                       0x00000008
  #define GL_POLYGON_STIPPLE_BIT                                               0x00000010
  #define GL_PIXEL_MODE_BIT                                                    0x00000020
  #define GL_LIGHTING_BIT                                                      0x00000040
  #define GL_FOG_BIT                                                           0x00000080
  #define GL_DEPTH_BUFFER_BIT                                                  0x00000100
  #define GL_ACCUM_BUFFER_BIT                                                  0x00000200
  #define GL_STENCIL_BUFFER_BIT                                                0x00000400
  #define GL_VIEWPORT_BIT                                                      0x00000800
  #define GL_TRANSFORM_BIT                                                     0x00001000
  #define GL_ENABLE_BIT                                                        0x00002000
  #define GL_COLOR_BUFFER_BIT                                                  0x00004000
  #define GL_HINT_BIT                                                          0x00008000
  #define GL_EVAL_BIT                                                          0x00010000
  #define GL_LIST_BIT                                                          0x00020000
  #define GL_TEXTURE_BIT                                                       0x00040000
  #define GL_SCISSOR_BIT                                                       0x00080000
  #define GL_ALL_ATTRIB_BITS                                                   0x000fffff
  #define GL_POINTS                                                            0x0000
  #define GL_LINES                                                             0x0001
  #define GL_LINE_LOOP                                                         0x0002
  #define GL_LINE_STRIP                                                        0x0003
  #define GL_TRIANGLES                                                         0x0004
  #define GL_TRIANGLE_STRIP                                                    0x0005
  #define GL_TRIANGLE_FAN                                                      0x0006
  #define GL_QUADS                                                             0x0007
  #define GL_QUAD_STRIP                                                        0x0008
  #define GL_POLYGON                                                           0x0009
  #define GL_ZERO                                                              0
  #define GL_ONE                                                               1
  #define GL_SRC_COLOR                                                         0x0300
  #define GL_ONE_MINUS_SRC_COLOR                                               0x0301
  #define GL_SRC_ALPHA                                                         0x0302
  #define GL_ONE_MINUS_SRC_ALPHA                                               0x0303
  #define GL_DST_ALPHA                                                         0x0304
  #define GL_ONE_MINUS_DST_ALPHA                                               0x0305
  #define GL_DST_COLOR                                                         0x0306
  #define GL_ONE_MINUS_DST_COLOR                                               0x0307
  #define GL_SRC_ALPHA_SATURATE                                                0x0308
  #define GL_TRUE                                                              1
  #define GL_FALSE                                                             0
  #define GL_CLIP_PLANE0                                                       0x3000
  #define GL_CLIP_PLANE1                                                       0x3001
  #define GL_CLIP_PLANE2                                                       0x3002
  #define GL_CLIP_PLANE3                                                       0x3003
  #define GL_CLIP_PLANE4                                                       0x3004
  #define GL_CLIP_PLANE5                                                       0x3005
  #define GL_BYTE                                                              0x1400
  #define GL_UNSIGNED_BYTE                                                     0x1401
  #define GL_SHORT                                                             0x1402
  #define GL_UNSIGNED_SHORT                                                    0x1403
  #define GL_INT                                                               0x1404
  #define GL_UNSIGNED_INT                                                      0x1405
  #define GL_FLOAT                                                             0x1406
  #define GL_2_BYTES                                                           0x1407
  #define GL_3_BYTES                                                           0x1408
  #define GL_4_BYTES                                                           0x1409
  #define GL_DOUBLE                                                            0x140A
  #define GL_NONE                                                              0
  #define GL_FRONT_LEFT                                                        0x0400
  #define GL_FRONT_RIGHT                                                       0x0401
  #define GL_BACK_LEFT                                                         0x0402
  #define GL_BACK_RIGHT                                                        0x0403
  #define GL_FRONT                                                             0x0404
  #define GL_BACK                                                              0x0405
  #define GL_LEFT                                                              0x0406
  #define GL_RIGHT                                                             0x0407
  #define GL_FRONT_AND_BACK                                                    0x0408
  #define GL_AUX0                                                              0x0409
  #define GL_AUX1                                                              0x040A
  #define GL_AUX2                                                              0x040B
  #define GL_AUX3                                                              0x040C
  #define GL_NO_ERROR                                                          0
  #define GL_INVALID_ENUM                                                      0x0500
  #define GL_INVALID_VALUE                                                     0x0501
  #define GL_INVALID_OPERATION                                                 0x0502
  #define GL_STACK_OVERFLOW                                                    0x0503
  #define GL_STACK_UNDERFLOW                                                   0x0504
  #define GL_OUT_OF_MEMORY                                                     0x0505
  #define GL_2D                                                                0x0600
  #define GL_3D                                                                0x0601
  #define GL_3D_COLOR                                                          0x0602
  #define GL_3D_COLOR_TEXTURE                                                  0x0603
  #define GL_4D_COLOR_TEXTURE                                                  0x0604
  #define GL_PASS_THROUGH_TOKEN                                                0x0700
  #define GL_POINT_TOKEN                                                       0x0701
  #define GL_LINE_TOKEN                                                        0x0702
  #define GL_POLYGON_TOKEN                                                     0x0703
  #define GL_BITMAP_TOKEN                                                      0x0704
  #define GL_DRAW_PIXEL_TOKEN                                                  0x0705
  #define GL_COPY_PIXEL_TOKEN                                                  0x0706
  #define GL_LINE_RESET_TOKEN                                                  0x0707
  #define GL_EXP                                                               0x0800
  #define GL_EXP2                                                              0x0801
  #define GL_CW                                                                0x0900
  #define GL_CCW                                                               0x0901
  #define GL_COEFF                                                             0x0A00
  #define GL_ORDER                                                             0x0A01
  #define GL_DOMAIN                                                            0x0A02
  #define GL_CURRENT_COLOR                                                     0x0B00
  #define GL_CURRENT_INDEX                                                     0x0B01
  #define GL_CURRENT_NORMAL                                                    0x0B02
  #define GL_CURRENT_TEXTURE_COORDS                                            0x0B03
  #define GL_CURRENT_RASTER_COLOR                                              0x0B04
  #define GL_CURRENT_RASTER_INDEX                                              0x0B05
  #define GL_CURRENT_RASTER_TEXTURE_COORDS                                     0x0B06
  #define GL_CURRENT_RASTER_POSITION                                           0x0B07
  #define GL_CURRENT_RASTER_POSITION_VALID                                     0x0B08
  #define GL_CURRENT_RASTER_DISTANCE                                           0x0B09
  #define GL_POINT_SMOOTH                                                      0x0B10
  #define GL_POINT_SIZE                                                        0x0B11
  #define GL_POINT_SIZE_RANGE                                                  0x0B12
  #define GL_POINT_SIZE_GRANULARITY                                            0x0B13
  #define GL_LINE_SMOOTH                                                       0x0B20
  #define GL_LINE_WIDTH                                                        0x0B21
  #define GL_LINE_WIDTH_RANGE                                                  0x0B22
  #define GL_LINE_WIDTH_GRANULARITY                                            0x0B23
  #define GL_LINE_STIPPLE                                                      0x0B24
  #define GL_LINE_STIPPLE_PATTERN                                              0x0B25
  #define GL_LINE_STIPPLE_REPEAT                                               0x0B26
  #define GL_LIST_MODE                                                         0x0B30
  #define GL_MAX_LIST_NESTING                                                  0x0B31
  #define GL_LIST_BASE                                                         0x0B32
  #define GL_LIST_INDEX                                                        0x0B33
  #define GL_POLYGON_MODE                                                      0x0B40
  #define GL_POLYGON_SMOOTH                                                    0x0B41
  #define GL_POLYGON_STIPPLE                                                   0x0B42
  #define GL_EDGE_FLAG                                                         0x0B43
  #define GL_CULL_FACE                                                         0x0B44
  #define GL_CULL_FACE_MODE                                                    0x0B45
  #define GL_FRONT_FACE                                                        0x0B46
  #define GL_LIGHTING                                                          0x0B50
  #define GL_LIGHT_MODEL_LOCAL_VIEWER                                          0x0B51
  #define GL_LIGHT_MODEL_TWO_SIDE                                              0x0B52
  #define GL_LIGHT_MODEL_AMBIENT                                               0x0B53
  #define GL_SHADE_MODEL                                                       0x0B54
  #define GL_COLOR_MATERIAL_FACE                                               0x0B55
  #define GL_COLOR_MATERIAL_PARAMETER                                          0x0B56
  #define GL_COLOR_MATERIAL                                                    0x0B57
  #define GL_FOG                                                               0x0B60
  #define GL_FOG_INDEX                                                         0x0B61
  #define GL_FOG_DENSITY                                                       0x0B62
  #define GL_FOG_START                                                         0x0B63
  #define GL_FOG_END                                                           0x0B64
  #define GL_FOG_MODE                                                          0x0B65
  #define GL_FOG_COLOR                                                         0x0B66
  #define GL_DEPTH_RANGE                                                       0x0B70
  #define GL_DEPTH_TEST                                                        0x0B71
  #define GL_DEPTH_WRITEMASK                                                   0x0B72
  #define GL_DEPTH_CLEAR_VALUE                                                 0x0B73
  #define GL_DEPTH_FUNC                                                        0x0B74
  #define GL_ACCUM_CLEAR_VALUE                                                 0x0B80
  #define GL_STENCIL_TEST                                                      0x0B90
  #define GL_STENCIL_CLEAR_VALUE                                               0x0B91
  #define GL_STENCIL_FUNC                                                      0x0B92
  #define GL_STENCIL_VALUE_MASK                                                0x0B93
  #define GL_STENCIL_FAIL                                                      0x0B94
  #define GL_STENCIL_PASS_DEPTH_FAIL                                           0x0B95
  #define GL_STENCIL_PASS_DEPTH_PASS                                           0x0B96
  #define GL_STENCIL_REF                                                       0x0B97
  #define GL_STENCIL_WRITEMASK                                                 0x0B98
  #define GL_MATRIX_MODE                                                       0x0BA0
  #define GL_NORMALIZE                                                         0x0BA1
  #define GL_VIEWPORT                                                          0x0BA2
  #define GL_MODELVIEW_STACK_DEPTH                                             0x0BA3
  #define GL_PROJECTION_STACK_DEPTH                                            0x0BA4
  #define GL_TEXTURE_STACK_DEPTH                                               0x0BA5
  #define GL_MODELVIEW_MATRIX                                                  0x0BA6
  #define GL_PROJECTION_MATRIX                                                 0x0BA7
  #define GL_TEXTURE_MATRIX                                                    0x0BA8
  #define GL_ATTRIB_STACK_DEPTH                                                0x0BB0
  #define GL_CLIENT_ATTRIB_STACK_DEPTH                                         0x0BB1
  #define GL_ALPHA_TEST                                                        0x0BC0
  #define GL_ALPHA_TEST_FUNC                                                   0x0BC1
  #define GL_ALPHA_TEST_REF                                                    0x0BC2
  #define GL_DITHER                                                            0x0BD0
  #define GL_BLEND_DST                                                         0x0BE0
  #define GL_BLEND_SRC                                                         0x0BE1
  #define GL_BLEND                                                             0x0BE2
  #define GL_LOGIC_OP_MODE                                                     0x0BF0
  #define GL_INDEX_LOGIC_OP                                                    0x0BF1
  #define GL_COLOR_LOGIC_OP                                                    0x0BF2
  #define GL_AUX_BUFFERS                                                       0x0C00
  #define GL_DRAW_BUFFER                                                       0x0C01
  #define GL_READ_BUFFER                                                       0x0C02
  #define GL_SCISSOR_BOX                                                       0x0C10
  #define GL_SCISSOR_TEST                                                      0x0C11
  #define GL_INDEX_CLEAR_VALUE                                                 0x0C20
  #define GL_INDEX_WRITEMASK                                                   0x0C21
  #define GL_COLOR_CLEAR_VALUE                                                 0x0C22
  #define GL_COLOR_WRITEMASK                                                   0x0C23
  #define GL_INDEX_MODE                                                        0x0C30
  #define GL_RGBA_MODE                                                         0x0C31
  #define GL_DOUBLEBUFFER                                                      0x0C32
  #define GL_STEREO                                                            0x0C33
  #define GL_RENDER_MODE                                                       0x0C40
  #define GL_PERSPECTIVE_CORRECTION_HINT                                       0x0C50
  #define GL_POINT_SMOOTH_HINT                                                 0x0C51
  #define GL_LINE_SMOOTH_HINT                                                  0x0C52
  #define GL_POLYGON_SMOOTH_HINT                                               0x0C53
  #define GL_FOG_HINT                                                          0x0C54
  #define GL_TEXTURE_GEN_S                                                     0x0C60
  #define GL_TEXTURE_GEN_T                                                     0x0C61
  #define GL_TEXTURE_GEN_R                                                     0x0C62
  #define GL_TEXTURE_GEN_Q                                                     0x0C63
  #define GL_PIXEL_MAP_I_TO_I                                                  0x0C70
  #define GL_PIXEL_MAP_S_TO_S                                                  0x0C71
  #define GL_PIXEL_MAP_I_TO_R                                                  0x0C72
  #define GL_PIXEL_MAP_I_TO_G                                                  0x0C73
  #define GL_PIXEL_MAP_I_TO_B                                                  0x0C74
  #define GL_PIXEL_MAP_I_TO_A                                                  0x0C75
  #define GL_PIXEL_MAP_R_TO_R                                                  0x0C76
  #define GL_PIXEL_MAP_G_TO_G                                                  0x0C77
  #define GL_PIXEL_MAP_B_TO_B                                                  0x0C78
  #define GL_PIXEL_MAP_A_TO_A                                                  0x0C79
  #define GL_PIXEL_MAP_I_TO_I_SIZE                                             0x0CB0
  #define GL_PIXEL_MAP_S_TO_S_SIZE                                             0x0CB1
  #define GL_PIXEL_MAP_I_TO_R_SIZE                                             0x0CB2
  #define GL_PIXEL_MAP_I_TO_G_SIZE                                             0x0CB3
  #define GL_PIXEL_MAP_I_TO_B_SIZE                                             0x0CB4
  #define GL_PIXEL_MAP_I_TO_A_SIZE                                             0x0CB5
  #define GL_PIXEL_MAP_R_TO_R_SIZE                                             0x0CB6
  #define GL_PIXEL_MAP_G_TO_G_SIZE                                             0x0CB7
  #define GL_PIXEL_MAP_B_TO_B_SIZE                                             0x0CB8
  #define GL_PIXEL_MAP_A_TO_A_SIZE                                             0x0CB9
  #define GL_UNPACK_SWAP_BYTES                                                 0x0CF0
  #define GL_UNPACK_LSB_FIRST                                                  0x0CF1
  #define GL_UNPACK_ROW_LENGTH                                                 0x0CF2
  #define GL_UNPACK_SKIP_ROWS                                                  0x0CF3
  #define GL_UNPACK_SKIP_PIXELS                                                0x0CF4
  #define GL_UNPACK_ALIGNMENT                                                  0x0CF5
  #define GL_PACK_SWAP_BYTES                                                   0x0D00
  #define GL_PACK_LSB_FIRST                                                    0x0D01
  #define GL_PACK_ROW_LENGTH                                                   0x0D02
  #define GL_PACK_SKIP_ROWS                                                    0x0D03
  #define GL_PACK_SKIP_PIXELS                                                  0x0D04
  #define GL_PACK_ALIGNMENT                                                    0x0D05
  #define GL_MAP_COLOR                                                         0x0D10
  #define GL_MAP_STENCIL                                                       0x0D11
  #define GL_INDEX_SHIFT                                                       0x0D12
  #define GL_INDEX_OFFSET                                                      0x0D13
  #define GL_RED_SCALE                                                         0x0D14
  #define GL_RED_BIAS                                                          0x0D15
  #define GL_ZOOM_X                                                            0x0D16
  #define GL_ZOOM_Y                                                            0x0D17
  #define GL_GREEN_SCALE                                                       0x0D18
  #define GL_GREEN_BIAS                                                        0x0D19
  #define GL_BLUE_SCALE                                                        0x0D1A
  #define GL_BLUE_BIAS                                                         0x0D1B
  #define GL_ALPHA_SCALE                                                       0x0D1C
  #define GL_ALPHA_BIAS                                                        0x0D1D
  #define GL_DEPTH_SCALE                                                       0x0D1E
  #define GL_DEPTH_BIAS                                                        0x0D1F
  #define GL_MAX_EVAL_ORDER                                                    0x0D30
  #define GL_MAX_LIGHTS                                                        0x0D31
  #define GL_MAX_CLIP_PLANES                                                   0x0D32
  #define GL_MAX_TEXTURE_SIZE                                                  0x0D33
  #define GL_MAX_PIXEL_MAP_TABLE                                               0x0D34
  #define GL_MAX_ATTRIB_STACK_DEPTH                                            0x0D35
  #define GL_MAX_MODELVIEW_STACK_DEPTH                                         0x0D36
  #define GL_MAX_NAME_STACK_DEPTH                                              0x0D37
  #define GL_MAX_PROJECTION_STACK_DEPTH                                        0x0D38
  #define GL_MAX_TEXTURE_STACK_DEPTH                                           0x0D39
  #define GL_MAX_VIEWPORT_DIMS                                                 0x0D3A
  #define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH                                     0x0D3B
  #define GL_SUBPIXEL_BITS                                                     0x0D50
  #define GL_INDEX_BITS                                                        0x0D51
  #define GL_RED_BITS                                                          0x0D52
  #define GL_GREEN_BITS                                                        0x0D53
  #define GL_BLUE_BITS                                                         0x0D54
  #define GL_ALPHA_BITS                                                        0x0D55
  #define GL_DEPTH_BITS                                                        0x0D56
  #define GL_STENCIL_BITS                                                      0x0D57
  #define GL_ACCUM_RED_BITS                                                    0x0D58
  #define GL_ACCUM_GREEN_BITS                                                  0x0D59
  #define GL_ACCUM_BLUE_BITS                                                   0x0D5A
  #define GL_ACCUM_ALPHA_BITS                                                  0x0D5B
  #define GL_NAME_STACK_DEPTH                                                  0x0D70
  #define GL_AUTO_NORMAL                                                       0x0D80
  #define GL_MAP1_COLOR_4                                                      0x0D90
  #define GL_MAP1_INDEX                                                        0x0D91
  #define GL_MAP1_NORMAL                                                       0x0D92
  #define GL_MAP1_TEXTURE_COORD_1                                              0x0D93
  #define GL_MAP1_TEXTURE_COORD_2                                              0x0D94
  #define GL_MAP1_TEXTURE_COORD_3                                              0x0D95
  #define GL_MAP1_TEXTURE_COORD_4                                              0x0D96
  #define GL_MAP1_VERTEX_3                                                     0x0D97
  #define GL_MAP1_VERTEX_4                                                     0x0D98
  #define GL_MAP2_COLOR_4                                                      0x0DB0
  #define GL_MAP2_INDEX                                                        0x0DB1
  #define GL_MAP2_NORMAL                                                       0x0DB2
  #define GL_MAP2_TEXTURE_COORD_1                                              0x0DB3
  #define GL_MAP2_TEXTURE_COORD_2                                              0x0DB4
  #define GL_MAP2_TEXTURE_COORD_3                                              0x0DB5
  #define GL_MAP2_TEXTURE_COORD_4                                              0x0DB6
  #define GL_MAP2_VERTEX_3                                                     0x0DB7
  #define GL_MAP2_VERTEX_4                                                     0x0DB8
  #define GL_MAP1_GRID_DOMAIN                                                  0x0DD0
  #define GL_MAP1_GRID_SEGMENTS                                                0x0DD1
  #define GL_MAP2_GRID_DOMAIN                                                  0x0DD2
  #define GL_MAP2_GRID_SEGMENTS                                                0x0DD3
  #define GL_TEXTURE_1D                                                        0x0DE0
  #define GL_TEXTURE_2D                                                        0x0DE1
  #define GL_FEEDBACK_BUFFER_POINTER                                           0x0DF0
  #define GL_FEEDBACK_BUFFER_SIZE                                              0x0DF1
  #define GL_FEEDBACK_BUFFER_TYPE                                              0x0DF2
  #define GL_SELECTION_BUFFER_POINTER                                          0x0DF3
  #define GL_SELECTION_BUFFER_SIZE                                             0x0DF4
  #define GL_TEXTURE_WIDTH                                                     0x1000
  #define GL_TEXTURE_HEIGHT                                                    0x1001
  #define GL_TEXTURE_INTERNAL_FORMAT                                           0x1003
  #define GL_TEXTURE_BORDER_COLOR                                              0x1004
  #define GL_TEXTURE_BORDER                                                    0x1005
  #define GL_DONT_CARE                                                         0x1100
  #define GL_FASTEST                                                           0x1101
  #define GL_NICEST                                                            0x1102
  #define GL_LIGHT0                                                            0x4000
  #define GL_LIGHT1                                                            0x4001
  #define GL_LIGHT2                                                            0x4002
  #define GL_LIGHT3                                                            0x4003
  #define GL_LIGHT4                                                            0x4004
  #define GL_LIGHT5                                                            0x4005
  #define GL_LIGHT6                                                            0x4006
  #define GL_LIGHT7                                                            0x4007
  #define GL_AMBIENT                                                           0x1200
  #define GL_DIFFUSE                                                           0x1201
  #define GL_SPECULAR                                                          0x1202
  #define GL_POSITION                                                          0x1203
  #define GL_SPOT_DIRECTION                                                    0x1204
  #define GL_SPOT_EXPONENT                                                     0x1205
  #define GL_SPOT_CUTOFF                                                       0x1206
  #define GL_CONSTANT_ATTENUATION                                              0x1207
  #define GL_LINEAR_ATTENUATION                                                0x1208
  #define GL_QUADRATIC_ATTENUATION                                             0x1209
  #define GL_COMPILE                                                           0x1300
  #define GL_COMPILE_AND_EXECUTE                                               0x1301
  #define GL_CLEAR                                                             0x1500
  #define GL_AND                                                               0x1501
  #define GL_AND_REVERSE                                                       0x1502
  #define GL_COPY                                                              0x1503
  #define GL_AND_INVERTED                                                      0x1504
  #define GL_NOOP                                                              0x1505
  #define GL_XOR                                                               0x1506
  #define GL_OR                                                                0x1507
  #define GL_NOR                                                               0x1508
  #define GL_EQUIV                                                             0x1509
  #define GL_INVERT                                                            0x150A
  #define GL_OR_REVERSE                                                        0x150B
  #define GL_COPY_INVERTED                                                     0x150C
  #define GL_OR_INVERTED                                                       0x150D
  #define GL_NAND                                                              0x150E
  #define GL_SET                                                               0x150F
  #define GL_EMISSION                                                          0x1600
  #define GL_SHININESS                                                         0x1601
  #define GL_AMBIENT_AND_DIFFUSE                                               0x1602
  #define GL_COLOR_INDEXES                                                     0x1603
  #define GL_MODELVIEW                                                         0x1700
  #define GL_PROJECTION                                                        0x1701
  #define GL_TEXTURE                                                           0x1702
  #define GL_COLOR                                                             0x1800
  #define GL_DEPTH                                                             0x1801
  #define GL_STENCIL                                                           0x1802
  #define GL_COLOR_INDEX                                                       0x1900
  #define GL_STENCIL_INDEX                                                     0x1901
  #define GL_DEPTH_COMPONENT                                                   0x1902
  #define GL_RED                                                               0x1903
  #define GL_GREEN                                                             0x1904
  #define GL_BLUE                                                              0x1905
  #define GL_ALPHA                                                             0x1906
  #define GL_RGB                                                               0x1907
  #define GL_RGBA                                                              0x1908
  #define GL_LUMINANCE                                                         0x1909
  #define GL_LUMINANCE_ALPHA                                                   0x190A
  #define GL_BITMAP                                                            0x1A00
  #define GL_POINT                                                             0x1B00
  #define GL_LINE                                                              0x1B01
  #define GL_FILL                                                              0x1B02
  #define GL_RENDER                                                            0x1C00
  #define GL_FEEDBACK                                                          0x1C01
  #define GL_SELECT                                                            0x1C02
  #define GL_FLAT                                                              0x1D00
  #define GL_SMOOTH                                                            0x1D01
  #define GL_KEEP                                                              0x1E00
  #define GL_REPLACE                                                           0x1E01
  #define GL_INCR                                                              0x1E02
  #define GL_DECR                                                              0x1E03
  #define GL_VENDOR                                                            0x1F00
  #define GL_RENDERER                                                          0x1F01
  #define GL_VERSION                                                           0x1F02
  #define GL_EXTENSIONS                                                        0x1F03
  #define GL_S                                                                 0x2000
  #define GL_T                                                                 0x2001
  #define GL_R                                                                 0x2002
  #define GL_Q                                                                 0x2003
  #define GL_MODULATE                                                          0x2100
  #define GL_DECAL                                                             0x2101
  #define GL_TEXTURE_ENV_MODE                                                  0x2200
  #define GL_TEXTURE_ENV_COLOR                                                 0x2201
  #define GL_TEXTURE_ENV                                                       0x2300
  #define GL_EYE_LINEAR                                                        0x2400
  #define GL_OBJECT_LINEAR                                                     0x2401
  #define GL_SPHERE_MAP                                                        0x2402
  #define GL_TEXTURE_GEN_MODE                                                  0x2500
  #define GL_OBJECT_PLANE                                                      0x2501
  #define GL_EYE_PLANE                                                         0x2502
  #define GL_NEAREST                                                           0x2600
  #define GL_LINEAR                                                            0x2601
  #define GL_NEAREST_MIPMAP_NEAREST                                            0x2700
  #define GL_LINEAR_MIPMAP_NEAREST                                             0x2701
  #define GL_NEAREST_MIPMAP_LINEAR                                             0x2702
  #define GL_LINEAR_MIPMAP_LINEAR                                              0x2703
  #define GL_TEXTURE_MAG_FILTER                                                0x2800
  #define GL_TEXTURE_MIN_FILTER                                                0x2801
  #define GL_TEXTURE_WRAP_S                                                    0x2802
  #define GL_TEXTURE_WRAP_T                                                    0x2803
  #define GL_CLAMP                                                             0x2900
  #define GL_REPEAT                                                            0x2901
  #define GL_CLIENT_PIXEL_STORE_BIT                                            0x00000001
  #define GL_CLIENT_VERTEX_ARRAY_BIT                                           0x00000002
  #define GL_CLIENT_ALL_ATTRIB_BITS                                            0xffffffff
  #define GL_POLYGON_OFFSET_FACTOR                                             0x8038
  #define GL_POLYGON_OFFSET_UNITS                                              0x2A00
  #define GL_POLYGON_OFFSET_POINT                                              0x2A01
  #define GL_POLYGON_OFFSET_LINE                                               0x2A02
  #define GL_POLYGON_OFFSET_FILL                                               0x8037
  #define GL_ALPHA4                                                            0x803B
  #define GL_ALPHA8                                                            0x803C
  #define GL_ALPHA12                                                           0x803D
  #define GL_ALPHA16                                                           0x803E
  #define GL_LUMINANCE4                                                        0x803F
  #define GL_LUMINANCE8                                                        0x8040
  #define GL_LUMINANCE12                                                       0x8041
  #define GL_LUMINANCE16                                                       0x8042
  #define GL_LUMINANCE4_ALPHA4                                                 0x8043
  #define GL_LUMINANCE6_ALPHA2                                                 0x8044
  #define GL_LUMINANCE8_ALPHA8                                                 0x8045
  #define GL_LUMINANCE12_ALPHA4                                                0x8046
  #define GL_LUMINANCE12_ALPHA12                                               0x8047
  #define GL_LUMINANCE16_ALPHA16                                               0x8048
  #define GL_INTENSITY                                                         0x8049
  #define GL_INTENSITY4                                                        0x804A
  #define GL_INTENSITY8                                                        0x804B
  #define GL_INTENSITY12                                                       0x804C
  #define GL_INTENSITY16                                                       0x804D
  #define GL_R3_G3_B2                                                          0x2A10
  #define GL_RGB4                                                              0x804F
  #define GL_RGB5                                                              0x8050
  #define GL_RGB8                                                              0x8051
  #define GL_RGB10                                                             0x8052
  #define GL_RGB12                                                             0x8053
  #define GL_RGB16                                                             0x8054
  #define GL_RGBA2                                                             0x8055
  #define GL_RGBA4                                                             0x8056
  #define GL_RGB5_A1                                                           0x8057
  #define GL_RGBA8                                                             0x8058
  #define GL_RGB10_A2                                                          0x8059
  #define GL_RGBA12                                                            0x805A
  #define GL_RGBA16                                                            0x805B
  #define GL_TEXTURE_RED_SIZE                                                  0x805C
  #define GL_TEXTURE_GREEN_SIZE                                                0x805D
  #define GL_TEXTURE_BLUE_SIZE                                                 0x805E
  #define GL_TEXTURE_ALPHA_SIZE                                                0x805F
  #define GL_TEXTURE_LUMINANCE_SIZE                                            0x8060
  #define GL_TEXTURE_INTENSITY_SIZE                                            0x8061
  #define GL_PROXY_TEXTURE_1D                                                  0x8063
  #define GL_PROXY_TEXTURE_2D                                                  0x8064
  #define GL_TEXTURE_PRIORITY                                                  0x8066
  #define GL_TEXTURE_RESIDENT                                                  0x8067
  #define GL_TEXTURE_BINDING_1D                                                0x8068
  #define GL_TEXTURE_BINDING_2D                                                0x8069
  #define GL_VERTEX_ARRAY                                                      0x8074
  #define GL_NORMAL_ARRAY                                                      0x8075
  #define GL_COLOR_ARRAY                                                       0x8076
  #define GL_INDEX_ARRAY                                                       0x8077
  #define GL_TEXTURE_COORD_ARRAY                                               0x8078
  #define GL_EDGE_FLAG_ARRAY                                                   0x8079
  #define GL_VERTEX_ARRAY_SIZE                                                 0x807A
  #define GL_VERTEX_ARRAY_TYPE                                                 0x807B
  #define GL_VERTEX_ARRAY_STRIDE                                               0x807C
  #define GL_NORMAL_ARRAY_TYPE                                                 0x807E
  #define GL_NORMAL_ARRAY_STRIDE                                               0x807F
  #define GL_COLOR_ARRAY_SIZE                                                  0x8081
  #define GL_COLOR_ARRAY_TYPE                                                  0x8082
  #define GL_COLOR_ARRAY_STRIDE                                                0x8083
  #define GL_INDEX_ARRAY_TYPE                                                  0x8085
  #define GL_INDEX_ARRAY_STRIDE                                                0x8086
  #define GL_TEXTURE_COORD_ARRAY_SIZE                                          0x8088
  #define GL_TEXTURE_COORD_ARRAY_TYPE                                          0x8089
  #define GL_TEXTURE_COORD_ARRAY_STRIDE                                        0x808A
  #define GL_EDGE_FLAG_ARRAY_STRIDE                                            0x808C
  #define GL_VERTEX_ARRAY_POINTER                                              0x808E
  #define GL_NORMAL_ARRAY_POINTER                                              0x808F
  #define GL_COLOR_ARRAY_POINTER                                               0x8090
  #define GL_INDEX_ARRAY_POINTER                                               0x8091
  #define GL_TEXTURE_COORD_ARRAY_POINTER                                       0x8092
  #define GL_EDGE_FLAG_ARRAY_POINTER                                           0x8093
  #define GL_V2F                                                               0x2A20
  #define GL_V3F                                                               0x2A21
  #define GL_C4UB_V2F                                                          0x2A22
  #define GL_C4UB_V3F                                                          0x2A23
  #define GL_C3F_V3F                                                           0x2A24
  #define GL_N3F_V3F                                                           0x2A25
  #define GL_C4F_N3F_V3F                                                       0x2A26
  #define GL_T2F_V3F                                                           0x2A27
  #define GL_T4F_V4F                                                           0x2A28
  #define GL_T2F_C4UB_V3F                                                      0x2A29
  #define GL_T2F_C3F_V3F                                                       0x2A2A
  #define GL_T2F_N3F_V3F                                                       0x2A2B
  #define GL_T2F_C4F_N3F_V3F                                                   0x2A2C
  #define GL_T4F_C4F_N3F_V4F                                                   0x2A2D

  typedef unsigned int GLenum;
  typedef unsigned char GLboolean;
  typedef unsigned int GLbitfield;
  typedef signed char GLbyte;
  typedef short GLshort;
  typedef int GLint;
  typedef int GLsizei;
  typedef unsigned char GLubyte;
  typedef unsigned short GLushort;
  typedef unsigned int GLuint;
  typedef float GLfloat;
  typedef float GLclampf;
  typedef double GLdouble;
  typedef double GLclampd;
  typedef void GLvoid;

  void SYS_APIENTRY glAccum( GLenum op, GLfloat value );
  void SYS_APIENTRY glAlphaFunc( GLenum func, GLclampf ref );
  GLboolean SYS_APIENTRY glAreTexturesResident( GLsizei n, const GLuint* textures, GLboolean* residences );
  void SYS_APIENTRY glArrayElement( GLint i );
  void SYS_APIENTRY glBegin( GLenum mode );
  void SYS_APIENTRY glBindTexture( GLenum target, GLuint texture );
  void SYS_APIENTRY glBitmap( GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte* bitmap );
  void SYS_APIENTRY glBlendFunc( GLenum sfactor, GLenum dfactor );
  void SYS_APIENTRY glCallList( GLuint list );
  void SYS_APIENTRY glCallLists( GLsizei n, GLenum type, const GLvoid* lists );
  void SYS_APIENTRY glClear( GLbitfield mask );
  void SYS_APIENTRY glClearAccum( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
  void SYS_APIENTRY glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
  void SYS_APIENTRY glClearDepth( GLclampd depth );
  void SYS_APIENTRY glClearIndex( GLfloat c );
  void SYS_APIENTRY glClearStencil( GLint s );
  void SYS_APIENTRY glClipPlane( GLenum plane, const GLdouble* equation );
  void SYS_APIENTRY glColor3b( GLbyte red, GLbyte green, GLbyte blue );
  void SYS_APIENTRY glColor3bv( const GLbyte* v );
  void SYS_APIENTRY glColor3d( GLdouble red, GLdouble green, GLdouble blue );
  void SYS_APIENTRY glColor3dv( const GLdouble* v );
  void SYS_APIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue );
  void SYS_APIENTRY glColor3fv( const GLfloat* v );
  void SYS_APIENTRY glColor3i( GLint red, GLint green, GLint blue );
  void SYS_APIENTRY glColor3iv( const GLint* v );
  void SYS_APIENTRY glColor3s( GLshort red, GLshort green, GLshort blue );
  void SYS_APIENTRY glColor3sv( const GLshort* v );
  void SYS_APIENTRY glColor3ub( GLubyte red, GLubyte green, GLubyte blue );
  void SYS_APIENTRY glColor3ubv( const GLubyte* v );
  void SYS_APIENTRY glColor3ui( GLuint red, GLuint green, GLuint blue );
  void SYS_APIENTRY glColor3uiv( const GLuint* v );
  void SYS_APIENTRY glColor3us( GLushort red, GLushort green, GLushort blue );
  void SYS_APIENTRY glColor3usv( const GLushort* v );
  void SYS_APIENTRY glColor4b( GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha );
  void SYS_APIENTRY glColor4bv( const GLbyte* v );
  void SYS_APIENTRY glColor4d( GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha );
  void SYS_APIENTRY glColor4dv( const GLdouble* v );
  void SYS_APIENTRY glColor4f( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha );
  void SYS_APIENTRY glColor4fv( const GLfloat* v );
  void SYS_APIENTRY glColor4i( GLint red, GLint green, GLint blue, GLint alpha );
  void SYS_APIENTRY glColor4iv( const GLint* v );
  void SYS_APIENTRY glColor4s( GLshort red, GLshort green, GLshort blue, GLshort alpha );
  void SYS_APIENTRY glColor4sv( const GLshort* v );
  void SYS_APIENTRY glColor4ub( GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha );
  void SYS_APIENTRY glColor4ubv( const GLubyte* v );
  void SYS_APIENTRY glColor4ui( GLuint red, GLuint green, GLuint blue, GLuint alpha );
  void SYS_APIENTRY glColor4uiv( const GLuint* v );
  void SYS_APIENTRY glColor4us( GLushort red, GLushort green, GLushort blue, GLushort alpha );
  void SYS_APIENTRY glColor4usv( const GLushort* v );
  void SYS_APIENTRY glColorMask( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha );
  void SYS_APIENTRY glColorMaterial( GLenum face, GLenum mode );
  void SYS_APIENTRY glColorPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer );
  void SYS_APIENTRY glCopyPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum type );
  void SYS_APIENTRY glCopyTexImage1D( GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border );
  void SYS_APIENTRY glCopyTexImage2D( GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border );
  void SYS_APIENTRY glCopyTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width );
  void SYS_APIENTRY glCopyTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height );
  void SYS_APIENTRY glCullFace( GLenum mode );
  void SYS_APIENTRY glDeleteLists( GLuint list, GLsizei range );
  void SYS_APIENTRY glDeleteTextures( GLsizei n, const GLuint* textures );
  void SYS_APIENTRY glDepthFunc( GLenum func );
  void SYS_APIENTRY glDepthMask( GLboolean flag );
  void SYS_APIENTRY glDepthRange( GLclampd zNear, GLclampd zFar );
  void SYS_APIENTRY glDisable( GLenum cap );
  void SYS_APIENTRY glDisableClientState( GLenum array );
  void SYS_APIENTRY glDrawArrays( GLenum mode, GLint first, GLsizei count );
  void SYS_APIENTRY glDrawBuffer( GLenum mode );
  void SYS_APIENTRY glDrawElements( GLenum mode, GLsizei count, GLenum type, const GLvoid* indices );
  void SYS_APIENTRY glDrawPixels( GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels );
  void SYS_APIENTRY glEdgeFlag( GLboolean flag );
  void SYS_APIENTRY glEdgeFlagPointer( GLsizei stride, const GLvoid* pointer );
  void SYS_APIENTRY glEdgeFlagv( const GLboolean* flag );
  void SYS_APIENTRY glEnable( GLenum cap );
  void SYS_APIENTRY glEnableClientState( GLenum array );
  void SYS_APIENTRY glEnd( void );
  void SYS_APIENTRY glEndList( void );
  void SYS_APIENTRY glEvalCoord1d( GLdouble u );
  void SYS_APIENTRY glEvalCoord1dv( const GLdouble* u );
  void SYS_APIENTRY glEvalCoord1f( GLfloat u );
  void SYS_APIENTRY glEvalCoord1fv( const GLfloat* u );
  void SYS_APIENTRY glEvalCoord2d( GLdouble u, GLdouble v );
  void SYS_APIENTRY glEvalCoord2dv( const GLdouble* u );
  void SYS_APIENTRY glEvalCoord2f( GLfloat u, GLfloat v );
  void SYS_APIENTRY glEvalCoord2fv( const GLfloat* u );
  void SYS_APIENTRY glEvalMesh1( GLenum mode, GLint i1, GLint i2 );
  void SYS_APIENTRY glEvalMesh2( GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2 );
  void SYS_APIENTRY glEvalPoint1( GLint i );
  void SYS_APIENTRY glEvalPoint2( GLint i, GLint j );
  void SYS_APIENTRY glFeedbackBuffer( GLsizei size, GLenum type, GLfloat* buffer );
  void SYS_APIENTRY glFinish( void );
  void SYS_APIENTRY glFlush( void );
  void SYS_APIENTRY glFogf( GLenum pname, GLfloat param );
  void SYS_APIENTRY glFogfv( GLenum pname, const GLfloat* params );
  void SYS_APIENTRY glFogi( GLenum pname, GLint param );
  void SYS_APIENTRY glFogiv( GLenum pname, const GLint* params );
  void SYS_APIENTRY glFrontFace( GLenum mode );
  void SYS_APIENTRY glFrustum( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar );
  GLuint SYS_APIENTRY glGenLists( GLsizei range );
  void SYS_APIENTRY glGenTextures( GLsizei n, GLuint* textures );
  void SYS_APIENTRY glGetBooleanv( GLenum pname, GLboolean* params );
  void SYS_APIENTRY glGetClipPlane( GLenum plane, GLdouble* equation );
  void SYS_APIENTRY glGetDoublev( GLenum pname, GLdouble* params );
  GLenum SYS_APIENTRY glGetError( void );
  void SYS_APIENTRY glGetFloatv( GLenum pname, GLfloat* params );
  void SYS_APIENTRY glGetIntegerv( GLenum pname, GLint* params );
  void SYS_APIENTRY glGetLightfv( GLenum light, GLenum pname, GLfloat* params );
  void SYS_APIENTRY glGetLightiv( GLenum light, GLenum pname, GLint* params );
  void SYS_APIENTRY glGetMapdv( GLenum target, GLenum query, GLdouble* v );
  void SYS_APIENTRY glGetMapfv( GLenum target, GLenum query, GLfloat* v );
  void SYS_APIENTRY glGetMapiv( GLenum target, GLenum query, GLint* v );
  void SYS_APIENTRY glGetMaterialfv( GLenum face, GLenum pname, GLfloat* params );
  void SYS_APIENTRY glGetMaterialiv( GLenum face, GLenum pname, GLint* params );
  void SYS_APIENTRY glGetPixelMapfv( GLenum map, GLfloat* values );
  void SYS_APIENTRY glGetPixelMapuiv( GLenum map, GLuint* values );
  void SYS_APIENTRY glGetPixelMapusv( GLenum map, GLushort* values );
  void SYS_APIENTRY glGetPointerv( GLenum pname, GLvoid** params );
  void SYS_APIENTRY glGetPolygonStipple( GLubyte* mask );
  const GLubyte*  SYS_APIENTRY glGetString( GLenum name );
  void SYS_APIENTRY glGetTexEnvfv( GLenum target, GLenum pname, GLfloat* params );
  void SYS_APIENTRY glGetTexEnviv( GLenum target, GLenum pname, GLint* params );
  void SYS_APIENTRY glGetTexGendv( GLenum coord, GLenum pname, GLdouble* params );
  void SYS_APIENTRY glGetTexGenfv( GLenum coord, GLenum pname, GLfloat* params );
  void SYS_APIENTRY glGetTexGeniv( GLenum coord, GLenum pname, GLint* params );
  void SYS_APIENTRY glGetTexImage( GLenum target, GLint level, GLenum format, GLenum type, GLvoid* pixels );
  void SYS_APIENTRY glGetTexLevelParameterfv( GLenum target, GLint level, GLenum pname, GLfloat* params );
  void SYS_APIENTRY glGetTexLevelParameteriv( GLenum target, GLint level, GLenum pname, GLint* params );
  void SYS_APIENTRY glGetTexParameterfv( GLenum target, GLenum pname, GLfloat* params );
  void SYS_APIENTRY glGetTexParameteriv( GLenum target, GLenum pname, GLint* params );
  void SYS_APIENTRY glHint( GLenum target, GLenum mode );
  void SYS_APIENTRY glIndexMask( GLuint mask );
  void SYS_APIENTRY glIndexPointer( GLenum type, GLsizei stride, const GLvoid* pointer );
  void SYS_APIENTRY glIndexd( GLdouble c );
  void SYS_APIENTRY glIndexdv( const GLdouble* c );
  void SYS_APIENTRY glIndexf( GLfloat c );
  void SYS_APIENTRY glIndexfv( const GLfloat* c );
  void SYS_APIENTRY glIndexi( GLint c );
  void SYS_APIENTRY glIndexiv( const GLint* c );
  void SYS_APIENTRY glIndexs( GLshort c );
  void SYS_APIENTRY glIndexsv( const GLshort* c );
  void SYS_APIENTRY glIndexub( GLubyte c );
  void SYS_APIENTRY glIndexubv( const GLubyte* c );
  void SYS_APIENTRY glInitNames( void );
  void SYS_APIENTRY glInterleavedArrays( GLenum format, GLsizei stride, const GLvoid* pointer );
  GLboolean SYS_APIENTRY glIsEnabled( GLenum cap );
  GLboolean SYS_APIENTRY glIsList( GLuint list );
  GLboolean SYS_APIENTRY glIsTexture( GLuint texture );
  void SYS_APIENTRY glLightModelf( GLenum pname, GLfloat param );
  void SYS_APIENTRY glLightModelfv( GLenum pname, const GLfloat* params );
  void SYS_APIENTRY glLightModeli( GLenum pname, GLint param );
  void SYS_APIENTRY glLightModeliv( GLenum pname, const GLint* params );
  void SYS_APIENTRY glLightf( GLenum light, GLenum pname, GLfloat param );
  void SYS_APIENTRY glLightfv( GLenum light, GLenum pname, const GLfloat* params );
  void SYS_APIENTRY glLighti( GLenum light, GLenum pname, GLint param );
  void SYS_APIENTRY glLightiv( GLenum light, GLenum pname, const GLint* params );
  void SYS_APIENTRY glLineStipple( GLint factor, GLushort pattern );
  void SYS_APIENTRY glLineWidth( GLfloat width );
  void SYS_APIENTRY glListBase( GLuint base );
  void SYS_APIENTRY glLoadIdentity( void );
  void SYS_APIENTRY glLoadMatrixd( const GLdouble* m );
  void SYS_APIENTRY glLoadMatrixf( const GLfloat* m );
  void SYS_APIENTRY glLoadName( GLuint name );
  void SYS_APIENTRY glLogicOp( GLenum opcode );
  void SYS_APIENTRY glMap1d( GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble* points );
  void SYS_APIENTRY glMap1f( GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points );
  void SYS_APIENTRY glMap2d( GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble* points );
  void SYS_APIENTRY glMap2f( GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points );
  void SYS_APIENTRY glMapGrid1d( GLint un, GLdouble u1, GLdouble u2 );
  void SYS_APIENTRY glMapGrid1f( GLint un, GLfloat u1, GLfloat u2 );
  void SYS_APIENTRY glMapGrid2d( GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2 );
  void SYS_APIENTRY glMapGrid2f( GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2 );
  void SYS_APIENTRY glMaterialf( GLenum face, GLenum pname, GLfloat param );
  void SYS_APIENTRY glMaterialfv( GLenum face, GLenum pname, const GLfloat* params );
  void SYS_APIENTRY glMateriali( GLenum face, GLenum pname, GLint param );
  void SYS_APIENTRY glMaterialiv( GLenum face, GLenum pname, const GLint* params );
  void SYS_APIENTRY glMatrixMode( GLenum mode );
  void SYS_APIENTRY glMultMatrixd( const GLdouble* m );
  void SYS_APIENTRY glMultMatrixf( const GLfloat* m );
  void SYS_APIENTRY glNewList( GLuint list, GLenum mode );
  void SYS_APIENTRY glNormal3b( GLbyte nx, GLbyte ny, GLbyte nz );
  void SYS_APIENTRY glNormal3bv( const GLbyte* v );
  void SYS_APIENTRY glNormal3d( GLdouble nx, GLdouble ny, GLdouble nz );
  void SYS_APIENTRY glNormal3dv( const GLdouble* v );
  void SYS_APIENTRY glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz );
  void SYS_APIENTRY glNormal3fv( const GLfloat* v );
  void SYS_APIENTRY glNormal3i( GLint nx, GLint ny, GLint nz );
  void SYS_APIENTRY glNormal3iv( const GLint* v );
  void SYS_APIENTRY glNormal3s( GLshort nx, GLshort ny, GLshort nz );
  void SYS_APIENTRY glNormal3sv( const GLshort* v );
  void SYS_APIENTRY glNormalPointer( GLenum type, GLsizei stride, const GLvoid* pointer );
  void SYS_APIENTRY glOrtho( GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar );
  void SYS_APIENTRY glPassThrough( GLfloat token );
  void SYS_APIENTRY glPixelMapfv( GLenum map, GLsizei mapsize, const GLfloat* values );
  void SYS_APIENTRY glPixelMapuiv( GLenum map, GLsizei mapsize, const GLuint* values );
  void SYS_APIENTRY glPixelMapusv( GLenum map, GLsizei mapsize, const GLushort* values );
  void SYS_APIENTRY glPixelStoref( GLenum pname, GLfloat param );
  void SYS_APIENTRY glPixelStorei( GLenum pname, GLint param );
  void SYS_APIENTRY glPixelTransferf( GLenum pname, GLfloat param );
  void SYS_APIENTRY glPixelTransferi( GLenum pname, GLint param );
  void SYS_APIENTRY glPixelZoom( GLfloat xfactor, GLfloat yfactor );
  void SYS_APIENTRY glPointSize( GLfloat size );
  void SYS_APIENTRY glPolygonMode( GLenum face, GLenum mode );
  void SYS_APIENTRY glPolygonOffset( GLfloat factor, GLfloat units );
  void SYS_APIENTRY glPolygonStipple( const GLubyte* mask );
  void SYS_APIENTRY glPopAttrib( void );
  void SYS_APIENTRY glPopClientAttrib( void );
  void SYS_APIENTRY glPopMatrix( void );
  void SYS_APIENTRY glPopName( void );
  void SYS_APIENTRY glPrioritizeTextures( GLsizei n, const GLuint* textures, const GLclampf* priorities );
  void SYS_APIENTRY glPushAttrib( GLbitfield mask );
  void SYS_APIENTRY glPushClientAttrib( GLbitfield mask );
  void SYS_APIENTRY glPushMatrix( void );
  void SYS_APIENTRY glPushName( GLuint name );
  void SYS_APIENTRY glRasterPos2d( GLdouble x, GLdouble y );
  void SYS_APIENTRY glRasterPos2dv( const GLdouble* v );
  void SYS_APIENTRY glRasterPos2f( GLfloat x, GLfloat y );
  void SYS_APIENTRY glRasterPos2fv( const GLfloat* v );
  void SYS_APIENTRY glRasterPos2i( GLint x, GLint y );
  void SYS_APIENTRY glRasterPos2iv( const GLint* v );
  void SYS_APIENTRY glRasterPos2s( GLshort x, GLshort y );
  void SYS_APIENTRY glRasterPos2sv( const GLshort* v );
  void SYS_APIENTRY glRasterPos3d( GLdouble x, GLdouble y, GLdouble z );
  void SYS_APIENTRY glRasterPos3dv( const GLdouble* v );
  void SYS_APIENTRY glRasterPos3f( GLfloat x, GLfloat y, GLfloat z );
  void SYS_APIENTRY glRasterPos3fv( const GLfloat* v );
  void SYS_APIENTRY glRasterPos3i( GLint x, GLint y, GLint z );
  void SYS_APIENTRY glRasterPos3iv( const GLint* v );
  void SYS_APIENTRY glRasterPos3s( GLshort x, GLshort y, GLshort z );
  void SYS_APIENTRY glRasterPos3sv( const GLshort* v );
  void SYS_APIENTRY glRasterPos4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w );
  void SYS_APIENTRY glRasterPos4dv( const GLdouble* v );
  void SYS_APIENTRY glRasterPos4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
  void SYS_APIENTRY glRasterPos4fv( const GLfloat* v );
  void SYS_APIENTRY glRasterPos4i( GLint x, GLint y, GLint z, GLint w );
  void SYS_APIENTRY glRasterPos4iv( const GLint* v );
  void SYS_APIENTRY glRasterPos4s( GLshort x, GLshort y, GLshort z, GLshort w );
  void SYS_APIENTRY glRasterPos4sv( const GLshort* v );
  void SYS_APIENTRY glReadBuffer( GLenum mode );
  void SYS_APIENTRY glReadPixels( GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels );
  void SYS_APIENTRY glRectd( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 );
  void SYS_APIENTRY glRectdv( const GLdouble* v1, const GLdouble* v2 );
  void SYS_APIENTRY glRectf( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 );
  void SYS_APIENTRY glRectfv( const GLfloat* v1, const GLfloat* v2 );
  void SYS_APIENTRY glRecti( GLint x1, GLint y1, GLint x2, GLint y2 );
  void SYS_APIENTRY glRectiv( const GLint* v1, const GLint* v2 );
  void SYS_APIENTRY glRects( GLshort x1, GLshort y1, GLshort x2, GLshort y2 );
  void SYS_APIENTRY glRectsv( const GLshort* v1, const GLshort* v2 );
  GLint SYS_APIENTRY glRenderMode( GLenum mode );
  void SYS_APIENTRY glRotated( GLdouble angle, GLdouble x, GLdouble y, GLdouble z );
  void SYS_APIENTRY glRotatef( GLfloat angle, GLfloat x, GLfloat y, GLfloat z );
  void SYS_APIENTRY glScaled( GLdouble x, GLdouble y, GLdouble z );
  void SYS_APIENTRY glScalef( GLfloat x, GLfloat y, GLfloat z );
  void SYS_APIENTRY glScissor( GLint x, GLint y, GLsizei width, GLsizei height );
  void SYS_APIENTRY glSelectBuffer( GLsizei size, GLuint* buffer );
  void SYS_APIENTRY glShadeModel( GLenum mode );
  void SYS_APIENTRY glStencilFunc( GLenum func, GLint ref, GLuint mask );
  void SYS_APIENTRY glStencilMask( GLuint mask );
  void SYS_APIENTRY glStencilOp( GLenum fail, GLenum zfail, GLenum zpass );
  void SYS_APIENTRY glTexCoord1d( GLdouble s );
  void SYS_APIENTRY glTexCoord1dv( const GLdouble* v );
  void SYS_APIENTRY glTexCoord1f( GLfloat s );
  void SYS_APIENTRY glTexCoord1fv( const GLfloat* v );
  void SYS_APIENTRY glTexCoord1i( GLint s );
  void SYS_APIENTRY glTexCoord1iv( const GLint* v );
  void SYS_APIENTRY glTexCoord1s( GLshort s );
  void SYS_APIENTRY glTexCoord1sv( const GLshort* v );
  void SYS_APIENTRY glTexCoord2d( GLdouble s, GLdouble t );
  void SYS_APIENTRY glTexCoord2dv( const GLdouble* v );
  void SYS_APIENTRY glTexCoord2f( GLfloat s, GLfloat t );
  void SYS_APIENTRY glTexCoord2fv( const GLfloat* v );
  void SYS_APIENTRY glTexCoord2i( GLint s, GLint t );
  void SYS_APIENTRY glTexCoord2iv( const GLint* v );
  void SYS_APIENTRY glTexCoord2s( GLshort s, GLshort t );
  void SYS_APIENTRY glTexCoord2sv( const GLshort* v );
  void SYS_APIENTRY glTexCoord3d( GLdouble s, GLdouble t, GLdouble r );
  void SYS_APIENTRY glTexCoord3dv( const GLdouble* v );
  void SYS_APIENTRY glTexCoord3f( GLfloat s, GLfloat t, GLfloat r );
  void SYS_APIENTRY glTexCoord3fv( const GLfloat* v );
  void SYS_APIENTRY glTexCoord3i( GLint s, GLint t, GLint r );
  void SYS_APIENTRY glTexCoord3iv( const GLint* v );
  void SYS_APIENTRY glTexCoord3s( GLshort s, GLshort t, GLshort r );
  void SYS_APIENTRY glTexCoord3sv( const GLshort* v );
  void SYS_APIENTRY glTexCoord4d( GLdouble s, GLdouble t, GLdouble r, GLdouble q );
  void SYS_APIENTRY glTexCoord4dv( const GLdouble* v );
  void SYS_APIENTRY glTexCoord4f( GLfloat s, GLfloat t, GLfloat r, GLfloat q );
  void SYS_APIENTRY glTexCoord4fv( const GLfloat* v );
  void SYS_APIENTRY glTexCoord4i( GLint s, GLint t, GLint r, GLint q );
  void SYS_APIENTRY glTexCoord4iv( const GLint* v );
  void SYS_APIENTRY glTexCoord4s( GLshort s, GLshort t, GLshort r, GLshort q );
  void SYS_APIENTRY glTexCoord4sv( const GLshort* v );
  void SYS_APIENTRY glTexCoordPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer );
  void SYS_APIENTRY glTexEnvf( GLenum target, GLenum pname, GLfloat param );
  void SYS_APIENTRY glTexEnvfv( GLenum target, GLenum pname, const GLfloat* params );
  void SYS_APIENTRY glTexEnvi( GLenum target, GLenum pname, GLint param );
  void SYS_APIENTRY glTexEnviv( GLenum target, GLenum pname, const GLint* params );
  void SYS_APIENTRY glTexGend( GLenum coord, GLenum pname, GLdouble param );
  void SYS_APIENTRY glTexGendv( GLenum coord, GLenum pname, const GLdouble* params );
  void SYS_APIENTRY glTexGenf( GLenum coord, GLenum pname, GLfloat param );
  void SYS_APIENTRY glTexGenfv( GLenum coord, GLenum pname, const GLfloat* params );
  void SYS_APIENTRY glTexGeni( GLenum coord, GLenum pname, GLint param );
  void SYS_APIENTRY glTexGeniv( GLenum coord, GLenum pname, const GLint* params );
  void SYS_APIENTRY glTexImage1D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels );
  void SYS_APIENTRY glTexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels );
  void SYS_APIENTRY glTexParameterf( GLenum target, GLenum pname, GLfloat param );
  void SYS_APIENTRY glTexParameterfv( GLenum target, GLenum pname, const GLfloat* params );
  void SYS_APIENTRY glTexParameteri( GLenum target, GLenum pname, GLint param );
  void SYS_APIENTRY glTexParameteriv( GLenum target, GLenum pname, const GLint* params );
  void SYS_APIENTRY glTexSubImage1D( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid* pixels );
  void SYS_APIENTRY glTexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels );
  void SYS_APIENTRY glTranslated( GLdouble x, GLdouble y, GLdouble z );
  void SYS_APIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z );
  void SYS_APIENTRY glVertex2d( GLdouble x, GLdouble y );
  void SYS_APIENTRY glVertex2dv( const GLdouble* v );
  void SYS_APIENTRY glVertex2f( GLfloat x, GLfloat y );
  void SYS_APIENTRY glVertex2fv( const GLfloat* v );
  void SYS_APIENTRY glVertex2i( GLint x, GLint y );
  void SYS_APIENTRY glVertex2iv( const GLint* v );
  void SYS_APIENTRY glVertex2s( GLshort x, GLshort y );
  void SYS_APIENTRY glVertex2sv( const GLshort* v );
  void SYS_APIENTRY glVertex3d( GLdouble x, GLdouble y, GLdouble z );
  void SYS_APIENTRY glVertex3dv( const GLdouble* v );
  void SYS_APIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z );
  void SYS_APIENTRY glVertex3fv( const GLfloat* v );
  void SYS_APIENTRY glVertex3i( GLint x, GLint y, GLint z );
  void SYS_APIENTRY glVertex3iv( const GLint* v );
  void SYS_APIENTRY glVertex3s( GLshort x, GLshort y, GLshort z );
  void SYS_APIENTRY glVertex3sv( const GLshort* v );
  void SYS_APIENTRY glVertex4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w );
  void SYS_APIENTRY glVertex4dv( const GLdouble* v );
  void SYS_APIENTRY glVertex4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w );
  void SYS_APIENTRY glVertex4fv( const GLfloat* v );
  void SYS_APIENTRY glVertex4i( GLint x, GLint y, GLint z, GLint w );
  void SYS_APIENTRY glVertex4iv( const GLint* v );
  void SYS_APIENTRY glVertex4s( GLshort x, GLshort y, GLshort z, GLshort w );
  void SYS_APIENTRY glVertex4sv( const GLshort* v );
  void SYS_APIENTRY glVertexPointer( GLint size, GLenum type, GLsizei stride, const GLvoid* pointer );
  void SYS_APIENTRY glViewport( GLint x, GLint y, GLsizei width, GLsizei height );
#endif

#ifndef GL_VERSION_1_2
  #define GL_VERSION_1_2 1
  #define APP_GL_VERSION_1_2_DEFINED

  #define GL_SMOOTH_POINT_SIZE_RANGE                                           0x0B12
  #define GL_SMOOTH_POINT_SIZE_GRANULARITY                                     0x0B13
  #define GL_SMOOTH_LINE_WIDTH_RANGE                                           0x0B22
  #define GL_SMOOTH_LINE_WIDTH_GRANULARITY                                     0x0B23
  #define GL_UNSIGNED_BYTE_3_3_2                                               0x8032
  #define GL_UNSIGNED_SHORT_4_4_4_4                                            0x8033
  #define GL_UNSIGNED_SHORT_5_5_5_1                                            0x8034
  #define GL_UNSIGNED_INT_8_8_8_8                                              0x8035
  #define GL_UNSIGNED_INT_10_10_10_2                                           0x8036
  #define GL_RESCALE_NORMAL                                                    0x803A
  #define GL_TEXTURE_BINDING_3D                                                0x806A
  #define GL_PACK_SKIP_IMAGES                                                  0x806B
  #define GL_PACK_IMAGE_HEIGHT                                                 0x806C
  #define GL_UNPACK_SKIP_IMAGES                                                0x806D
  #define GL_UNPACK_IMAGE_HEIGHT                                               0x806E
  #define GL_TEXTURE_3D                                                        0x806F
  #define GL_PROXY_TEXTURE_3D                                                  0x8070
  #define GL_TEXTURE_DEPTH                                                     0x8071
  #define GL_TEXTURE_WRAP_R                                                    0x8072
  #define GL_MAX_3D_TEXTURE_SIZE                                               0x8073
  #define GL_BGR                                                               0x80E0
  #define GL_BGRA                                                              0x80E1
  #define GL_MAX_ELEMENTS_VERTICES                                             0x80E8
  #define GL_MAX_ELEMENTS_INDICES                                              0x80E9
  #define GL_CLAMP_TO_EDGE                                                     0x812F
  #define GL_TEXTURE_MIN_LOD                                                   0x813A
  #define GL_TEXTURE_MAX_LOD                                                   0x813B
  #define GL_TEXTURE_BASE_LEVEL                                                0x813C
  #define GL_TEXTURE_MAX_LEVEL                                                 0x813D
  #define GL_LIGHT_MODEL_COLOR_CONTROL                                         0x81F8
  #define GL_SINGLE_COLOR                                                      0x81F9
  #define GL_SEPARATE_SPECULAR_COLOR                                           0x81FA
  #define GL_UNSIGNED_BYTE_2_3_3_REV                                           0x8362
  #define GL_UNSIGNED_SHORT_5_6_5                                              0x8363
  #define GL_UNSIGNED_SHORT_5_6_5_REV                                          0x8364
  #define GL_UNSIGNED_SHORT_4_4_4_4_REV                                        0x8365
  #define GL_UNSIGNED_SHORT_1_5_5_5_REV                                        0x8366
  #define GL_UNSIGNED_INT_8_8_8_8_REV                                          0x8367
  #define GL_UNSIGNED_INT_2_10_10_10_REV                                       0x8368
  #define GL_ALIASED_POINT_SIZE_RANGE                                          0x846D
  #define GL_ALIASED_LINE_WIDTH_RANGE                                          0x846E

  typedef void (SYS_APIENTRY *app_glblendcolor_t)( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha );
  typedef void (SYS_APIENTRY *app_glblendequation_t)( GLenum mode );
  typedef void (SYS_APIENTRY *app_glcopytexsubimage3d_t)( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height );
  typedef void (SYS_APIENTRY *app_gldrawrangeelements_t)( GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid* indices );
  typedef void (SYS_APIENTRY *app_glteximage3d_t)( GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid* pixels );
  typedef void (SYS_APIENTRY *app_gltexsubimage3d_t)( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid* pixels );

  SYS_API extern app_glblendcolor_t glBlendColor;
  SYS_API extern app_glblendequation_t glBlendEquation;
  SYS_API extern app_glcopytexsubimage3d_t glCopyTexSubImage3D;
  SYS_API extern app_gldrawrangeelements_t glDrawRangeElements;
  SYS_API extern app_glteximage3d_t glTexImage3D;
  SYS_API extern app_gltexsubimage3d_t glTexSubImage3D;
#endif

#ifndef GL_VERSION_1_3
  #define GL_VERSION_1_3 1
  #define APP_GL_VERSION_1_3_DEFINED

  #define GL_MULTISAMPLE                                                       0x809D
  #define GL_SAMPLE_ALPHA_TO_COVERAGE                                          0x809E
  #define GL_SAMPLE_ALPHA_TO_ONE                                               0x809F
  #define GL_SAMPLE_COVERAGE                                                   0x80A0
  #define GL_SAMPLE_BUFFERS                                                    0x80A8
  #define GL_SAMPLES                                                           0x80A9
  #define GL_SAMPLE_COVERAGE_VALUE                                             0x80AA
  #define GL_SAMPLE_COVERAGE_INVERT                                            0x80AB
  #define GL_CLAMP_TO_BORDER                                                   0x812D
  #define GL_TEXTURE0                                                          0x84C0
  #define GL_TEXTURE1                                                          0x84C1
  #define GL_TEXTURE2                                                          0x84C2
  #define GL_TEXTURE3                                                          0x84C3
  #define GL_TEXTURE4                                                          0x84C4
  #define GL_TEXTURE5                                                          0x84C5
  #define GL_TEXTURE6                                                          0x84C6
  #define GL_TEXTURE7                                                          0x84C7
  #define GL_TEXTURE8                                                          0x84C8
  #define GL_TEXTURE9                                                          0x84C9
  #define GL_TEXTURE10                                                         0x84CA
  #define GL_TEXTURE11                                                         0x84CB
  #define GL_TEXTURE12                                                         0x84CC
  #define GL_TEXTURE13                                                         0x84CD
  #define GL_TEXTURE14                                                         0x84CE
  #define GL_TEXTURE15                                                         0x84CF
  #define GL_TEXTURE16                                                         0x84D0
  #define GL_TEXTURE17                                                         0x84D1
  #define GL_TEXTURE18                                                         0x84D2
  #define GL_TEXTURE19                                                         0x84D3
  #define GL_TEXTURE20                                                         0x84D4
  #define GL_TEXTURE21                                                         0x84D5
  #define GL_TEXTURE22                                                         0x84D6
  #define GL_TEXTURE23                                                         0x84D7
  #define GL_TEXTURE24                                                         0x84D8
  #define GL_TEXTURE25                                                         0x84D9
  #define GL_TEXTURE26                                                         0x84DA
  #define GL_TEXTURE27                                                         0x84DB
  #define GL_TEXTURE28                                                         0x84DC
  #define GL_TEXTURE29                                                         0x84DD
  #define GL_TEXTURE30                                                         0x84DE
  #define GL_TEXTURE31                                                         0x84DF
  #define GL_ACTIVE_TEXTURE                                                    0x84E0
  #define GL_CLIENT_ACTIVE_TEXTURE                                             0x84E1
  #define GL_MAX_TEXTURE_UNITS                                                 0x84E2
  #define GL_TRANSPOSE_MODELVIEW_MATRIX                                        0x84E3
  #define GL_TRANSPOSE_PROJECTION_MATRIX                                       0x84E4
  #define GL_TRANSPOSE_TEXTURE_MATRIX                                          0x84E5
  #define GL_TRANSPOSE_COLOR_MATRIX                                            0x84E6
  #define GL_SUBTRACT                                                          0x84E7
  #define GL_COMPRESSED_ALPHA                                                  0x84E9
  #define GL_COMPRESSED_LUMINANCE                                              0x84EA
  #define GL_COMPRESSED_LUMINANCE_ALPHA                                        0x84EB
  #define GL_COMPRESSED_INTENSITY                                              0x84EC
  #define GL_COMPRESSED_RGB                                                    0x84ED
  #define GL_COMPRESSED_RGBA                                                   0x84EE
  #define GL_TEXTURE_COMPRESSION_HINT                                          0x84EF
  #define GL_NORMAL_MAP                                                        0x8511
  #define GL_REFLECTION_MAP                                                    0x8512
  #define GL_TEXTURE_CUBE_MAP                                                  0x8513
  #define GL_TEXTURE_BINDING_CUBE_MAP                                          0x8514
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_X                                       0x8515
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_X                                       0x8516
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_Y                                       0x8517
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y                                       0x8518
  #define GL_TEXTURE_CUBE_MAP_POSITIVE_Z                                       0x8519
  #define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z                                       0x851A
  #define GL_PROXY_TEXTURE_CUBE_MAP                                            0x851B
  #define GL_MAX_CUBE_MAP_TEXTURE_SIZE                                         0x851C
  #define GL_COMBINE                                                           0x8570
  #define GL_COMBINE_RGB                                                       0x8571
  #define GL_COMBINE_ALPHA                                                     0x8572
  #define GL_RGB_SCALE                                                         0x8573
  #define GL_ADD_SIGNED                                                        0x8574
  #define GL_INTERPOLATE                                                       0x8575
  #define GL_CONSTANT                                                          0x8576
  #define GL_PRIMARY_COLOR                                                     0x8577
  #define GL_PREVIOUS                                                          0x8578
  #define GL_SOURCE0_RGB                                                       0x8580
  #define GL_SOURCE1_RGB                                                       0x8581
  #define GL_SOURCE2_RGB                                                       0x8582
  #define GL_SOURCE0_ALPHA                                                     0x8588
  #define GL_SOURCE1_ALPHA                                                     0x8589
  #define GL_SOURCE2_ALPHA                                                     0x858A
  #define GL_OPERAND0_RGB                                                      0x8590
  #define GL_OPERAND1_RGB                                                      0x8591
  #define GL_OPERAND2_RGB                                                      0x8592
  #define GL_OPERAND0_ALPHA                                                    0x8598
  #define GL_OPERAND1_ALPHA                                                    0x8599
  #define GL_OPERAND2_ALPHA                                                    0x859A
  #define GL_TEXTURE_COMPRESSED_IMAGE_SIZE                                     0x86A0
  #define GL_TEXTURE_COMPRESSED                                                0x86A1
  #define GL_NUM_COMPRESSED_TEXTURE_FORMATS                                    0x86A2
  #define GL_COMPRESSED_TEXTURE_FORMATS                                        0x86A3
  #define GL_DOT3_RGB                                                          0x86AE
  #define GL_DOT3_RGBA                                                         0x86AF
  #define GL_MULTISAMPLE_BIT                                                   0x20000000

  typedef void (SYS_APIENTRY *app_glActiveTexture_t)( GLenum texture );
  typedef void (SYS_APIENTRY *app_glClientActiveTexture_t)( GLenum texture );
  typedef void (SYS_APIENTRY *app_glCompressedTexImage1D_t)( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid* data );
  typedef void (SYS_APIENTRY *app_glCompressedTexImage2D_t)( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data );
  typedef void (SYS_APIENTRY *app_glCompressedTexImage3D_t)( GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid* data );
  typedef void (SYS_APIENTRY *app_glCompressedTexSubImage1D_t)( GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid* data );
  typedef void (SYS_APIENTRY *app_glCompressedTexSubImage2D_t)( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data );
  typedef void (SYS_APIENTRY *app_glCompressedTexSubImage3D_t)( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid* data );
  typedef void (SYS_APIENTRY *app_glGetCompressedTexImage_t)( GLenum target, GLint level, GLvoid* img );
  typedef void (SYS_APIENTRY *app_glLoadTransposeMatrixd_t)( const GLdouble* m );
  typedef void (SYS_APIENTRY *app_glLoadTransposeMatrixf_t)( const GLfloat* m );
  typedef void (SYS_APIENTRY *app_glMultTransposeMatrixd_t)( const GLdouble* m );
  typedef void (SYS_APIENTRY *app_glMultTransposeMatrixf_t)( const GLfloat* m );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord1d_t)( GLenum target, GLdouble s );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord1dv_t)( GLenum target, const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord1f_t)( GLenum target, GLfloat s );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord1fv_t)( GLenum target, const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord1i_t)( GLenum target, GLint s );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord1iv_t)( GLenum target, const GLint* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord1s_t)( GLenum target, GLshort s );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord1sv_t)( GLenum target, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord2d_t)( GLenum target, GLdouble s, GLdouble t );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord2dv_t)( GLenum target, const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord2f_t)( GLenum target, GLfloat s, GLfloat t );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord2fv_t)( GLenum target, const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord2i_t)( GLenum target, GLint s, GLint t );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord2iv_t)( GLenum target, const GLint* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord2s_t)( GLenum target, GLshort s, GLshort t );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord2sv_t)( GLenum target, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord3d_t)( GLenum target, GLdouble s, GLdouble t, GLdouble r );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord3dv_t)( GLenum target, const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord3f_t)( GLenum target, GLfloat s, GLfloat t, GLfloat r );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord3fv_t)( GLenum target, const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord3i_t)( GLenum target, GLint s, GLint t, GLint r );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord3iv_t)( GLenum target, const GLint* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord3s_t)( GLenum target, GLshort s, GLshort t, GLshort r );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord3sv_t)( GLenum target, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord4d_t)( GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord4dv_t)( GLenum target, const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord4f_t)( GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord4fv_t)( GLenum target, const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord4i_t)( GLenum target, GLint s, GLint t, GLint r, GLint q );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord4iv_t)( GLenum target, const GLint* v );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord4s_t)( GLenum target, GLshort s, GLshort t, GLshort r, GLshort q );
  typedef void (SYS_APIENTRY *app_glMultiTexCoord4sv_t)( GLenum target, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glSampleCoverage_t)( GLclampf value, GLboolean invert );

  SYS_API extern app_glActiveTexture_t glActiveTexture;
  SYS_API extern app_glClientActiveTexture_t glClientActiveTexture;
  SYS_API extern app_glCompressedTexImage1D_t glCompressedTexImage1D;
  SYS_API extern app_glCompressedTexImage2D_t glCompressedTexImage2D;
  SYS_API extern app_glCompressedTexImage3D_t glCompressedTexImage3D;
  SYS_API extern app_glCompressedTexSubImage1D_t glCompressedTexSubImage1D;
  SYS_API extern app_glCompressedTexSubImage2D_t glCompressedTexSubImage2D;
  SYS_API extern app_glCompressedTexSubImage3D_t glCompressedTexSubImage3D;
  SYS_API extern app_glGetCompressedTexImage_t glGetCompressedTexImage;
  SYS_API extern app_glLoadTransposeMatrixd_t glLoadTransposeMatrixd;
  SYS_API extern app_glLoadTransposeMatrixf_t glLoadTransposeMatrixf;
  SYS_API extern app_glMultTransposeMatrixd_t glMultTransposeMatrixd;
  SYS_API extern app_glMultTransposeMatrixf_t glMultTransposeMatrixf;
  SYS_API extern app_glMultiTexCoord1d_t glMultiTexCoord1d;
  SYS_API extern app_glMultiTexCoord1dv_t glMultiTexCoord1dv;
  SYS_API extern app_glMultiTexCoord1f_t glMultiTexCoord1f;
  SYS_API extern app_glMultiTexCoord1fv_t glMultiTexCoord1fv;
  SYS_API extern app_glMultiTexCoord1i_t glMultiTexCoord1i;
  SYS_API extern app_glMultiTexCoord1iv_t glMultiTexCoord1iv;
  SYS_API extern app_glMultiTexCoord1s_t glMultiTexCoord1s;
  SYS_API extern app_glMultiTexCoord1sv_t glMultiTexCoord1sv;
  SYS_API extern app_glMultiTexCoord2d_t glMultiTexCoord2d;
  SYS_API extern app_glMultiTexCoord2dv_t glMultiTexCoord2dv;
  SYS_API extern app_glMultiTexCoord2f_t glMultiTexCoord2f;
  SYS_API extern app_glMultiTexCoord2fv_t glMultiTexCoord2fv;
  SYS_API extern app_glMultiTexCoord2i_t glMultiTexCoord2i;
  SYS_API extern app_glMultiTexCoord2iv_t glMultiTexCoord2iv;
  SYS_API extern app_glMultiTexCoord2s_t glMultiTexCoord2s;
  SYS_API extern app_glMultiTexCoord2sv_t glMultiTexCoord2sv;
  SYS_API extern app_glMultiTexCoord3d_t glMultiTexCoord3d;
  SYS_API extern app_glMultiTexCoord3dv_t glMultiTexCoord3dv;
  SYS_API extern app_glMultiTexCoord3f_t glMultiTexCoord3f;
  SYS_API extern app_glMultiTexCoord3fv_t glMultiTexCoord3fv;
  SYS_API extern app_glMultiTexCoord3i_t glMultiTexCoord3i;
  SYS_API extern app_glMultiTexCoord3iv_t glMultiTexCoord3iv;
  SYS_API extern app_glMultiTexCoord3s_t glMultiTexCoord3s;
  SYS_API extern app_glMultiTexCoord3sv_t glMultiTexCoord3sv;
  SYS_API extern app_glMultiTexCoord4d_t glMultiTexCoord4d;
  SYS_API extern app_glMultiTexCoord4dv_t glMultiTexCoord4dv;
  SYS_API extern app_glMultiTexCoord4f_t glMultiTexCoord4f;
  SYS_API extern app_glMultiTexCoord4fv_t glMultiTexCoord4fv;
  SYS_API extern app_glMultiTexCoord4i_t glMultiTexCoord4i;
  SYS_API extern app_glMultiTexCoord4iv_t glMultiTexCoord4iv;
  SYS_API extern app_glMultiTexCoord4s_t glMultiTexCoord4s;
  SYS_API extern app_glMultiTexCoord4sv_t glMultiTexCoord4sv;
  SYS_API extern app_glSampleCoverage_t glSampleCoverage;
#endif

#ifndef GL_VERSION_1_4
  #define GL_VERSION_1_4 1
  #define APP_GL_VERSION_1_4_DEFINED

  #define GL_BLEND_DST_RGB                                                     0x80C8
  #define GL_BLEND_SRC_RGB                                                     0x80C9
  #define GL_BLEND_DST_ALPHA                                                   0x80CA
  #define GL_BLEND_SRC_ALPHA                                                   0x80CB
  #define GL_POINT_SIZE_MIN                                                    0x8126
  #define GL_POINT_SIZE_MAX                                                    0x8127
  #define GL_POINT_FADE_THRESHOLD_SIZE                                         0x8128
  #define GL_POINT_DISTANCE_ATTENUATION                                        0x8129
  #define GL_GENERATE_MIPMAP                                                   0x8191
  #define GL_GENERATE_MIPMAP_HINT                                              0x8192
  #define GL_DEPTH_COMPONENT16                                                 0x81A5
  #define GL_DEPTH_COMPONENT24                                                 0x81A6
  #define GL_DEPTH_COMPONENT32                                                 0x81A7
  #define GL_MIRRORED_REPEAT                                                   0x8370
  #define GL_FOG_COORDINATE_SOURCE                                             0x8450
  #define GL_FOG_COORDINATE                                                    0x8451
  #define GL_FRAGMENT_DEPTH                                                    0x8452
  #define GL_CURRENT_FOG_COORDINATE                                            0x8453
  #define GL_FOG_COORDINATE_ARRAY_TYPE                                         0x8454
  #define GL_FOG_COORDINATE_ARRAY_STRIDE                                       0x8455
  #define GL_FOG_COORDINATE_ARRAY_POINTER                                      0x8456
  #define GL_FOG_COORDINATE_ARRAY                                              0x8457
  #define GL_COLOR_SUM                                                         0x8458
  #define GL_CURRENT_SECONDARY_COLOR                                           0x8459
  #define GL_SECONDARY_COLOR_ARRAY_SIZE                                        0x845A
  #define GL_SECONDARY_COLOR_ARRAY_TYPE                                        0x845B
  #define GL_SECONDARY_COLOR_ARRAY_STRIDE                                      0x845C
  #define GL_SECONDARY_COLOR_ARRAY_POINTER                                     0x845D
  #define GL_SECONDARY_COLOR_ARRAY                                             0x845E
  #define GL_MAX_TEXTURE_LOD_BIAS                                              0x84FD
  #define GL_TEXTURE_FILTER_CONTROL                                            0x8500
  #define GL_TEXTURE_LOD_BIAS                                                  0x8501
  #define GL_INCR_WRAP                                                         0x8507
  #define GL_DECR_WRAP                                                         0x8508
  #define GL_TEXTURE_DEPTH_SIZE                                                0x884A
  #define GL_DEPTH_TEXTURE_MODE                                                0x884B
  #define GL_TEXTURE_COMPARE_MODE                                              0x884C
  #define GL_TEXTURE_COMPARE_FUNC                                              0x884D
  #define GL_COMPARE_R_TO_TEXTURE                                              0x884E

  typedef void (SYS_APIENTRY *app_glBlendFuncSeparate_t)( GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha );
  typedef void (SYS_APIENTRY *app_glFogCoordd_t)( GLdouble coord );
  typedef void (SYS_APIENTRY *app_glFogCoorddv_t)( const GLdouble* coord );
  typedef void (SYS_APIENTRY *app_glFogCoordf_t)( GLfloat coord );
  typedef void (SYS_APIENTRY *app_glFogCoordfv_t)( const GLfloat* coord );
  typedef void (SYS_APIENTRY *app_glFogCoordPointer_t)( GLenum type, GLsizei stride, const GLvoid* pointer );
  typedef void (SYS_APIENTRY *app_glMultiDrawArrays_t)( GLenum mode, GLint* first, GLsizei* count, GLsizei primcount );
  typedef void (SYS_APIENTRY *app_glMultiDrawElements_t)( GLenum mode, const GLsizei* count, GLenum type, const GLvoid** indices, GLsizei primcount );
  typedef void (SYS_APIENTRY *app_glPointParameterf_t)( GLenum pname, GLfloat param );
  typedef void (SYS_APIENTRY *app_glPointParameterfv_t)( GLenum pname, const GLfloat* params );
  typedef void (SYS_APIENTRY *app_glPointParameteri_t)( GLenum pname, GLint param );
  typedef void (SYS_APIENTRY *app_glPointParameteriv_t)( GLenum pname, const GLint* params );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3b_t)( GLbyte red, GLbyte green, GLbyte blue );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3bv_t)( const GLbyte* v );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3d_t)( GLdouble red, GLdouble green, GLdouble blue );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3dv_t)( const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3f_t)( GLfloat red, GLfloat green, GLfloat blue );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3fv_t)( const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3i_t)( GLint red, GLint green, GLint blue );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3iv_t)( const GLint* v );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3s_t)( GLshort red, GLshort green, GLshort blue );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3sv_t)( const GLshort* v );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3ub_t)( GLubyte red, GLubyte green, GLubyte blue );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3ubv_t)( const GLubyte* v );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3ui_t)( GLuint red, GLuint green, GLuint blue );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3uiv_t)( const GLuint* v );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3us_t)( GLushort red, GLushort green, GLushort blue );
  typedef void (SYS_APIENTRY *app_glSecondaryColor3usv_t)( const GLushort* v );
  typedef void (SYS_APIENTRY *app_glSecondaryColorPointer_t)( GLint size, GLenum type, GLsizei stride, const GLvoid *pointer );
  typedef void (SYS_APIENTRY *app_glWindowPos2d_t)( GLdouble x, GLdouble y );
  typedef void (SYS_APIENTRY *app_glWindowPos2dv_t)( const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glWindowPos2f_t)( GLfloat x, GLfloat y );
  typedef void (SYS_APIENTRY *app_glWindowPos2fv_t)( const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glWindowPos2i_t)( GLint x, GLint y );
  typedef void (SYS_APIENTRY *app_glWindowPos2iv_t)( const GLint* v );
  typedef void (SYS_APIENTRY *app_glWindowPos2s_t)( GLshort x, GLshort y );
  typedef void (SYS_APIENTRY *app_glWindowPos2sv_t)( const GLshort* v );
  typedef void (SYS_APIENTRY *app_glWindowPos3d_t)( GLdouble x, GLdouble y, GLdouble z );
  typedef void (SYS_APIENTRY *app_glWindowPos3dv_t)( const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glWindowPos3f_t)( GLfloat x, GLfloat y, GLfloat z );
  typedef void (SYS_APIENTRY *app_glWindowPos3fv_t)( const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glWindowPos3i_t)( GLint x, GLint y, GLint z );
  typedef void (SYS_APIENTRY *app_glWindowPos3iv_t)( const GLint* v );
  typedef void (SYS_APIENTRY *app_glWindowPos3s_t)( GLshort x, GLshort y, GLshort z );
  typedef void (SYS_APIENTRY *app_glWindowPos3sv_t)( const GLshort* v );

  SYS_API extern app_glBlendFuncSeparate_t glBlendFuncSeparate;
  SYS_API extern app_glFogCoordd_t glFogCoordd;
  SYS_API extern app_glFogCoorddv_t glFogCoorddv;
  SYS_API extern app_glFogCoordf_t glFogCoordf;
  SYS_API extern app_glFogCoordfv_t glFogCoordfv;
  SYS_API extern app_glFogCoordPointer_t glFogCoordPointer;
  SYS_API extern app_glMultiDrawArrays_t glMultiDrawArrays;
  SYS_API extern app_glMultiDrawElements_t glMultiDrawElements;
  SYS_API extern app_glPointParameterf_t glPointParameterf;
  SYS_API extern app_glPointParameterfv_t glPointParameterfv;
  SYS_API extern app_glPointParameteri_t glPointParameteri;
  SYS_API extern app_glPointParameteriv_t glPointParameteriv;
  SYS_API extern app_glSecondaryColor3b_t glSecondaryColor3b;
  SYS_API extern app_glSecondaryColor3bv_t glSecondaryColor3bv;
  SYS_API extern app_glSecondaryColor3d_t glSecondaryColor3d;
  SYS_API extern app_glSecondaryColor3dv_t glSecondaryColor3dv;
  SYS_API extern app_glSecondaryColor3f_t glSecondaryColor3f;
  SYS_API extern app_glSecondaryColor3fv_t glSecondaryColor3fv;
  SYS_API extern app_glSecondaryColor3i_t glSecondaryColor3i;
  SYS_API extern app_glSecondaryColor3iv_t glSecondaryColor3iv;
  SYS_API extern app_glSecondaryColor3s_t glSecondaryColor3s;
  SYS_API extern app_glSecondaryColor3sv_t glSecondaryColor3sv;
  SYS_API extern app_glSecondaryColor3ub_t glSecondaryColor3ub;
  SYS_API extern app_glSecondaryColor3ubv_t glSecondaryColor3ubv;
  SYS_API extern app_glSecondaryColor3ui_t glSecondaryColor3ui;
  SYS_API extern app_glSecondaryColor3uiv_t glSecondaryColor3uiv;
  SYS_API extern app_glSecondaryColor3us_t glSecondaryColor3us;
  SYS_API extern app_glSecondaryColor3usv_t glSecondaryColor3usv;
  SYS_API extern app_glSecondaryColorPointer_t glSecondaryColorPointer;
  SYS_API extern app_glWindowPos2d_t glWindowPos2d;
  SYS_API extern app_glWindowPos2dv_t glWindowPos2dv;
  SYS_API extern app_glWindowPos2f_t glWindowPos2f;
  SYS_API extern app_glWindowPos2fv_t glWindowPos2fv;
  SYS_API extern app_glWindowPos2i_t glWindowPos2i;
  SYS_API extern app_glWindowPos2iv_t glWindowPos2iv;
  SYS_API extern app_glWindowPos2s_t glWindowPos2s;
  SYS_API extern app_glWindowPos2sv_t glWindowPos2sv;
  SYS_API extern app_glWindowPos3d_t glWindowPos3d;
  SYS_API extern app_glWindowPos3dv_t glWindowPos3dv;
  SYS_API extern app_glWindowPos3f_t glWindowPos3f;
  SYS_API extern app_glWindowPos3fv_t glWindowPos3fv;
  SYS_API extern app_glWindowPos3i_t glWindowPos3i;
  SYS_API extern app_glWindowPos3iv_t glWindowPos3iv;
  SYS_API extern app_glWindowPos3s_t glWindowPos3s;
  SYS_API extern app_glWindowPos3sv_t glWindowPos3sv;
#endif

#ifndef GL_VERSION_1_5
  #define GL_VERSION_1_5 1
  #define APP_GL_VERSION_1_5_DEFINED

  #define GL_FOG_COORD_SRC                                                     0x8450
  #define GL_FOG_COORD                                                         0x8451
  #define GL_CURRENT_FOG_COORD                                                 0x8453
  #define GL_FOG_COORD_ARRAY_TYPE                                              0x8454
  #define GL_FOG_COORD_ARRAY_STRIDE                                            0x8455
  #define GL_FOG_COORD_ARRAY_POINTER                                           0x8456
  #define GL_FOG_COORD_ARRAY                                                   0x8457
  #define GL_SRC0_RGB                                                          0x8580
  #define GL_SRC1_RGB                                                          0x8581
  #define GL_SRC2_RGB                                                          0x8582
  #define GL_SRC0_ALPHA                                                        0x8588
  #define GL_SRC1_ALPHA                                                        0x8589
  #define GL_SRC2_ALPHA                                                        0x858A
  #define GL_BUFFER_SIZE                                                       0x8764
  #define GL_BUFFER_USAGE                                                      0x8765
  #define GL_QUERY_COUNTER_BITS                                                0x8864
  #define GL_CURRENT_QUERY                                                     0x8865
  #define GL_QUERY_RESULT                                                      0x8866
  #define GL_QUERY_RESULT_AVAILABLE                                            0x8867
  #define GL_ARRAY_BUFFER                                                      0x8892
  #define GL_ELEMENT_ARRAY_BUFFER                                              0x8893
  #define GL_ARRAY_BUFFER_BINDING                                              0x8894
  #define GL_ELEMENT_ARRAY_BUFFER_BINDING                                      0x8895
  #define GL_VERTEX_ARRAY_BUFFER_BINDING                                       0x8896
  #define GL_NORMAL_ARRAY_BUFFER_BINDING                                       0x8897
  #define GL_COLOR_ARRAY_BUFFER_BINDING                                        0x8898
  #define GL_INDEX_ARRAY_BUFFER_BINDING                                        0x8899
  #define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING                                0x889A
  #define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING                                    0x889B
  #define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING                              0x889C
  #define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING                               0x889D
  #define GL_FOG_COORD_ARRAY_BUFFER_BINDING                                    0x889D
  #define GL_WEIGHT_ARRAY_BUFFER_BINDING                                       0x889E
  #define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING                                0x889F
  #define GL_READ_ONLY                                                         0x88B8
  #define GL_WRITE_ONLY                                                        0x88B9
  #define GL_READ_WRITE                                                        0x88BA
  #define GL_BUFFER_ACCESS                                                     0x88BB
  #define GL_BUFFER_MAPPED                                                     0x88BC
  #define GL_BUFFER_MAP_POINTER                                                0x88BD
  #define GL_STREAM_DRAW                                                       0x88E0
  #define GL_STREAM_READ                                                       0x88E1
  #define GL_STREAM_COPY                                                       0x88E2
  #define GL_STATIC_DRAW                                                       0x88E4
  #define GL_STATIC_READ                                                       0x88E5
  #define GL_STATIC_COPY                                                       0x88E6
  #define GL_DYNAMIC_DRAW                                                      0x88E8
  #define GL_DYNAMIC_READ                                                      0x88E9
  #define GL_DYNAMIC_COPY                                                      0x88EA
  #define GL_SAMPLES_PASSED                                                    0x8914

  typedef ptrdiff_t GLintptr;
  typedef ptrdiff_t GLsizeiptr;

  typedef void (SYS_APIENTRY *app_glBeginQuery_t)( GLenum target, GLuint id );
  typedef void (SYS_APIENTRY *app_glBindBuffer_t)( GLenum target, GLuint buffer );
  typedef void (SYS_APIENTRY *app_glBufferData_t)( GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage );
  typedef void (SYS_APIENTRY *app_glBufferSubData_t)( GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data );
  typedef void (SYS_APIENTRY *app_glDeleteBuffers_t)( GLsizei n, const GLuint* buffers );
  typedef void (SYS_APIENTRY *app_glDeleteQueries_t)( GLsizei n, const GLuint* ids );
  typedef void (SYS_APIENTRY *app_glEndQuery_t)( GLenum target );
  typedef void (SYS_APIENTRY *app_glGenBuffers_t)( GLsizei n, GLuint* buffers );
  typedef void (SYS_APIENTRY *app_glGenQueries_t)( GLsizei n, GLuint* ids );
  typedef void (SYS_APIENTRY *app_glGetBufferParameteriv_t)( GLenum target, GLenum pname, GLint* params );
  typedef void (SYS_APIENTRY *app_glGetBufferPointerv_t)( GLenum target, GLenum pname, GLvoid** params );
  typedef void (SYS_APIENTRY *app_glGetBufferSubData_t)( GLenum target, GLintptr offset, GLsizeiptr size, GLvoid* data );
  typedef void (SYS_APIENTRY *app_glGetQueryObjectiv_t)( GLuint id, GLenum pname, GLint* params );
  typedef void (SYS_APIENTRY *app_glGetQueryObjectuiv_t)( GLuint id, GLenum pname, GLuint* params );
  typedef void (SYS_APIENTRY *app_glGetQueryiv_t)( GLenum target, GLenum pname, GLint* params );
  typedef GLboolean (SYS_APIENTRY *app_glIsBuffer_t)( GLuint buffer );
  typedef GLboolean (SYS_APIENTRY *app_glIsQuery_t)( GLuint id );
  typedef GLvoid* (SYS_APIENTRY *app_glMapBuffer_t)( GLenum target, GLenum access );
  typedef GLboolean (SYS_APIENTRY *app_glUnmapBuffer_t)( GLenum target );

  SYS_API extern app_glBeginQuery_t glBeginQuery;
  SYS_API extern app_glBindBuffer_t glBindBuffer;
  SYS_API extern app_glBufferData_t glBufferData;
  SYS_API extern app_glBufferSubData_t glBufferSubData;
  SYS_API extern app_glDeleteBuffers_t glDeleteBuffers;
  SYS_API extern app_glDeleteQueries_t glDeleteQueries;
  SYS_API extern app_glEndQuery_t glEndQuery;
  SYS_API extern app_glGenBuffers_t glGenBuffers;
  SYS_API extern app_glGenQueries_t glGenQueries;
  SYS_API extern app_glGetBufferParameteriv_t glGetBufferParameteriv;
  SYS_API extern app_glGetBufferPointerv_t glGetBufferPointerv;
  SYS_API extern app_glGetBufferSubData_t glGetBufferSubData;
  SYS_API extern app_glGetQueryObjectiv_t glGetQueryObjectiv;
  SYS_API extern app_glGetQueryObjectuiv_t glGetQueryObjectuiv;
  SYS_API extern app_glGetQueryiv_t glGetQueryiv;
  SYS_API extern app_glIsBuffer_t glIsBuffer;
  SYS_API extern app_glIsQuery_t glIsQuery;
  SYS_API extern app_glMapBuffer_t glMapBuffer;
  SYS_API extern app_glUnmapBuffer_t glUnmapBuffer;
#endif

#ifndef GL_VERSION_2_0
  #define GL_VERSION_2_0 1
  #define APP_GL_VERSION_2_0_DEFINED

  #define GL_BLEND_EQUATION_RGB                                                0x8009
  #define GL_VERTEX_ATTRIB_ARRAY_ENABLED                                       0x8622
  #define GL_VERTEX_ATTRIB_ARRAY_SIZE                                          0x8623
  #define GL_VERTEX_ATTRIB_ARRAY_STRIDE                                        0x8624
  #define GL_VERTEX_ATTRIB_ARRAY_TYPE                                          0x8625
  #define GL_CURRENT_VERTEX_ATTRIB                                             0x8626
  #define GL_VERTEX_PROGRAM_POINT_SIZE                                         0x8642
  #define GL_VERTEX_PROGRAM_TWO_SIDE                                           0x8643
  #define GL_VERTEX_ATTRIB_ARRAY_POINTER                                       0x8645
  #define GL_STENCIL_BACK_FUNC                                                 0x8800
  #define GL_STENCIL_BACK_FAIL                                                 0x8801
  #define GL_STENCIL_BACK_PASS_DEPTH_FAIL                                      0x8802
  #define GL_STENCIL_BACK_PASS_DEPTH_PASS                                      0x8803
  #define GL_MAX_DRAW_BUFFERS                                                  0x8824
  #define GL_DRAW_BUFFER0                                                      0x8825
  #define GL_DRAW_BUFFER1                                                      0x8826
  #define GL_DRAW_BUFFER2                                                      0x8827
  #define GL_DRAW_BUFFER3                                                      0x8828
  #define GL_DRAW_BUFFER4                                                      0x8829
  #define GL_DRAW_BUFFER5                                                      0x882A
  #define GL_DRAW_BUFFER6                                                      0x882B
  #define GL_DRAW_BUFFER7                                                      0x882C
  #define GL_DRAW_BUFFER8                                                      0x882D
  #define GL_DRAW_BUFFER9                                                      0x882E
  #define GL_DRAW_BUFFER10                                                     0x882F
  #define GL_DRAW_BUFFER11                                                     0x8830
  #define GL_DRAW_BUFFER12                                                     0x8831
  #define GL_DRAW_BUFFER13                                                     0x8832
  #define GL_DRAW_BUFFER14                                                     0x8833
  #define GL_DRAW_BUFFER15                                                     0x8834
  #define GL_BLEND_EQUATION_ALPHA                                              0x883D
  #define GL_POINT_SPRITE                                                      0x8861
  #define GL_COORD_REPLACE                                                     0x8862
  #define GL_MAX_VERTEX_ATTRIBS                                                0x8869
  #define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED                                    0x886A
  #define GL_MAX_TEXTURE_COORDS                                                0x8871
  #define GL_MAX_TEXTURE_IMAGE_UNITS                                           0x8872
  #define GL_FRAGMENT_SHADER                                                   0x8B30
  #define GL_VERTEX_SHADER                                                     0x8B31
  #define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS                                   0x8B49
  #define GL_MAX_VERTEX_UNIFORM_COMPONENTS                                     0x8B4A
  #define GL_MAX_VARYING_FLOATS                                                0x8B4B
  #define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS                                    0x8B4C
  #define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS                                  0x8B4D
  #define GL_SHADER_TYPE                                                       0x8B4F
  #define GL_FLOAT_VEC2                                                        0x8B50
  #define GL_FLOAT_VEC3                                                        0x8B51
  #define GL_FLOAT_VEC4                                                        0x8B52
  #define GL_INT_VEC2                                                          0x8B53
  #define GL_INT_VEC3                                                          0x8B54
  #define GL_INT_VEC4                                                          0x8B55
  #define GL_BOOL                                                              0x8B56
  #define GL_BOOL_VEC2                                                         0x8B57
  #define GL_BOOL_VEC3                                                         0x8B58
  #define GL_BOOL_VEC4                                                         0x8B59
  #define GL_FLOAT_MAT2                                                        0x8B5A
  #define GL_FLOAT_MAT3                                                        0x8B5B
  #define GL_FLOAT_MAT4                                                        0x8B5C
  #define GL_SAMPLER_1D                                                        0x8B5D
  #define GL_SAMPLER_2D                                                        0x8B5E
  #define GL_SAMPLER_3D                                                        0x8B5F
  #define GL_SAMPLER_CUBE                                                      0x8B60
  #define GL_SAMPLER_1D_SHADOW                                                 0x8B61
  #define GL_SAMPLER_2D_SHADOW                                                 0x8B62
  #define GL_DELETE_STATUS                                                     0x8B80
  #define GL_COMPILE_STATUS                                                    0x8B81
  #define GL_LINK_STATUS                                                       0x8B82
  #define GL_VALIDATE_STATUS                                                   0x8B83
  #define GL_INFO_LOG_LENGTH                                                   0x8B84
  #define GL_ATTACHED_SHADERS                                                  0x8B85
  #define GL_ACTIVE_UNIFORMS                                                   0x8B86
  #define GL_ACTIVE_UNIFORM_MAX_LENGTH                                         0x8B87
  #define GL_SHADER_SOURCE_LENGTH                                              0x8B88
  #define GL_ACTIVE_ATTRIBUTES                                                 0x8B89
  #define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH                                       0x8B8A
  #define GL_FRAGMENT_SHADER_DERIVATIVE_HINT                                   0x8B8B
  #define GL_SHADING_LANGUAGE_VERSION                                          0x8B8C
  #define GL_CURRENT_PROGRAM                                                   0x8B8D
  #define GL_POINT_SPRITE_COORD_ORIGIN                                         0x8CA0
  #define GL_LOWER_LEFT                                                        0x8CA1
  #define GL_UPPER_LEFT                                                        0x8CA2
  #define GL_STENCIL_BACK_REF                                                  0x8CA3
  #define GL_STENCIL_BACK_VALUE_MASK                                           0x8CA4
  #define GL_STENCIL_BACK_WRITEMASK                                            0x8CA5

  typedef char GLchar;

  typedef void (SYS_APIENTRY *app_glAttachShader_t)( GLuint program, GLuint shader );
  typedef void (SYS_APIENTRY *app_glBindAttribLocation_t)( GLuint program, GLuint index, const GLchar* name );
  typedef void (SYS_APIENTRY *app_glBlendEquationSeparate_t)( GLenum modeRGB, GLenum modeAlpha );
  typedef void (SYS_APIENTRY *app_glCompileShader_t)( GLuint shader );
  typedef GLuint (SYS_APIENTRY *app_glCreateProgram_t)( void );
  typedef GLuint (SYS_APIENTRY *app_glCreateShader_t)( GLenum type );
  typedef void (SYS_APIENTRY *app_glDeleteProgram_t)( GLuint program );
  typedef void (SYS_APIENTRY *app_glDeleteShader_t)( GLuint shader );
  typedef void (SYS_APIENTRY *app_glDetachShader_t)( GLuint program, GLuint shader );
  typedef void (SYS_APIENTRY *app_glDisableVertexAttribArray_t)( GLuint index );
  typedef void (SYS_APIENTRY *app_glDrawBuffers_t)( GLsizei n, const GLenum* bufs );
  typedef void (SYS_APIENTRY *app_glEnableVertexAttribArray_t)( GLuint index );
  typedef void (SYS_APIENTRY *app_glGetActiveAttrib_t)( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name );
  typedef void (SYS_APIENTRY *app_glGetActiveUniform_t)( GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name );
  typedef void (SYS_APIENTRY *app_glGetAttachedShaders_t)( GLuint program, GLsizei maxCount, GLsizei* count, GLuint* obj );
  typedef GLint (SYS_APIENTRY *app_glGetAttribLocation_t)( GLuint program, const GLchar* name );
  typedef void (SYS_APIENTRY *app_glGetProgramInfoLog_t)( GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog );
  typedef void (SYS_APIENTRY *app_glGetProgramiv_t)( GLuint program, GLenum pname, GLint* params );
  typedef void (SYS_APIENTRY *app_glGetShaderInfoLog_t)( GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog );
  typedef void (SYS_APIENTRY *app_glGetShaderiv_t)( GLuint shader, GLenum pname, GLint* params );
  typedef void (SYS_APIENTRY *app_glGetShaderSource_t)( GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* source );
  typedef GLint (SYS_APIENTRY *app_glGetUniformLocation_t)( GLuint program, const GLchar* name );
  typedef void (SYS_APIENTRY *app_glGetUniformfv_t)( GLuint program, GLint location, GLfloat* params );
  typedef void (SYS_APIENTRY *app_glGetUniformiv_t)( GLuint program, GLint location, GLint* params );
  typedef void (SYS_APIENTRY *app_glGetVertexAttribdv_t)( GLuint index, GLenum pname, GLdouble* params );
  typedef void (SYS_APIENTRY *app_glGetVertexAttribfv_t)( GLuint index, GLenum pname, GLfloat* params );
  typedef void (SYS_APIENTRY *app_glGetVertexAttribiv_t)( GLuint index, GLenum pname, GLint* params );
  typedef void (SYS_APIENTRY *app_glGetVertexAttribPointerv_t)( GLuint index, GLenum pname, GLvoid** pointer );
  typedef GLboolean (SYS_APIENTRY *app_glIsProgram_t)( GLuint program );
  typedef GLboolean (SYS_APIENTRY *app_glIsShader_t)( GLuint shader );
  typedef void (SYS_APIENTRY *app_glLinkProgram_t)( GLuint program );
  typedef void (SYS_APIENTRY *app_glShaderSource_t)( GLuint shader, GLsizei count, const GLchar** string, const GLint* length );
  typedef void (SYS_APIENTRY *app_glStencilFuncSeparate_t)( GLenum frontfunc, GLenum backfunc, GLint ref, GLuint mask );
  typedef void (SYS_APIENTRY *app_glStencilMaskSeparate_t)( GLenum face, GLuint mask );
  typedef void (SYS_APIENTRY *app_glStencilOpSeparate_t)( GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass );
  typedef void (SYS_APIENTRY *app_glUniform1f_t)( GLint location, GLfloat v0 );
  typedef void (SYS_APIENTRY *app_glUniform1fv_t)( GLint location, GLsizei count, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniform1i_t)( GLint location, GLint v0 );
  typedef void (SYS_APIENTRY *app_glUniform1iv_t)( GLint location, GLsizei count, const GLint* value );
  typedef void (SYS_APIENTRY *app_glUniform2f_t)( GLint location, GLfloat v0, GLfloat v1 );
  typedef void (SYS_APIENTRY *app_glUniform2fv_t)( GLint location, GLsizei count, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniform2i_t)( GLint location, GLint v0, GLint v1 );
  typedef void (SYS_APIENTRY *app_glUniform2iv_t)( GLint location, GLsizei count, const GLint* value );
  typedef void (SYS_APIENTRY *app_glUniform3f_t)( GLint location, GLfloat v0, GLfloat v1, GLfloat v2 );
  typedef void (SYS_APIENTRY *app_glUniform3fv_t)( GLint location, GLsizei count, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniform3i_t)( GLint location, GLint v0, GLint v1, GLint v2 );
  typedef void (SYS_APIENTRY *app_glUniform3iv_t)( GLint location, GLsizei count, const GLint* value );
  typedef void (SYS_APIENTRY *app_glUniform4f_t)( GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3 );
  typedef void (SYS_APIENTRY *app_glUniform4fv_t)( GLint location, GLsizei count, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniform4i_t)( GLint location, GLint v0, GLint v1, GLint v2, GLint v3 );
  typedef void (SYS_APIENTRY *app_glUniform4iv_t)( GLint location, GLsizei count, const GLint* value );
  typedef void (SYS_APIENTRY *app_glUniformMatrix2fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniformMatrix3fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniformMatrix4fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUseProgram_t)( GLuint program );
  typedef void (SYS_APIENTRY *app_glValidateProgram_t)( GLuint program );
  typedef void (SYS_APIENTRY *app_glVertexAttrib1d_t)( GLuint index, GLdouble x );
  typedef void (SYS_APIENTRY *app_glVertexAttrib1dv_t)( GLuint index, const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib1f_t)( GLuint index, GLfloat x );
  typedef void (SYS_APIENTRY *app_glVertexAttrib1fv_t)( GLuint index, const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib1s_t)( GLuint index, GLshort x );
  typedef void (SYS_APIENTRY *app_glVertexAttrib1sv_t)( GLuint index, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib2d_t)( GLuint index, GLdouble x, GLdouble y );
  typedef void (SYS_APIENTRY *app_glVertexAttrib2dv_t)( GLuint index, const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib2f_t)( GLuint index, GLfloat x, GLfloat y );
  typedef void (SYS_APIENTRY *app_glVertexAttrib2fv_t)( GLuint index, const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib2s_t)( GLuint index, GLshort x, GLshort y );
  typedef void (SYS_APIENTRY *app_glVertexAttrib2sv_t)( GLuint index, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib3d_t)( GLuint index, GLdouble x, GLdouble y, GLdouble z );
  typedef void (SYS_APIENTRY *app_glVertexAttrib3dv_t)( GLuint index, const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib3f_t)( GLuint index, GLfloat x, GLfloat y, GLfloat z );
  typedef void (SYS_APIENTRY *app_glVertexAttrib3fv_t)( GLuint index, const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib3s_t)( GLuint index, GLshort x, GLshort y, GLshort z );
  typedef void (SYS_APIENTRY *app_glVertexAttrib3sv_t)( GLuint index, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4Nbv_t)( GLuint index, const GLbyte* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4Niv_t)( GLuint index, const GLint* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4Nsv_t)( GLuint index, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4Nub_t)( GLuint index, GLubyte x, GLubyte y, GLubyte z, GLubyte w );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4Nubv_t)( GLuint index, const GLubyte* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4Nuiv_t)( GLuint index, const GLuint* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4Nusv_t)( GLuint index, const GLushort* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4bv_t)( GLuint index, const GLbyte* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4d_t)( GLuint index, GLdouble x, GLdouble y, GLdouble z, GLdouble w );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4dv_t)( GLuint index, const GLdouble* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4f_t)( GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4fv_t)( GLuint index, const GLfloat* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4iv_t)( GLuint index, const GLint* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4s_t)( GLuint index, GLshort x, GLshort y, GLshort z, GLshort w );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4sv_t)( GLuint index, const GLshort* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4ubv_t)( GLuint index, const GLubyte* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4uiv_t)( GLuint index, const GLuint* v );
  typedef void (SYS_APIENTRY *app_glVertexAttrib4usv_t)( GLuint index, const GLushort* v );
  typedef void (SYS_APIENTRY *app_glVertexAttribPointer_t)( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer );

  SYS_API extern app_glAttachShader_t glAttachShader;
  SYS_API extern app_glBindAttribLocation_t glBindAttribLocation;
  SYS_API extern app_glBlendEquationSeparate_t glBlendEquationSeparate;
  SYS_API extern app_glCompileShader_t glCompileShader;
  SYS_API extern app_glCreateProgram_t glCreateProgram;
  SYS_API extern app_glCreateShader_t glCreateShader;
  SYS_API extern app_glDeleteProgram_t glDeleteProgram;
  SYS_API extern app_glDeleteShader_t glDeleteShader;
  SYS_API extern app_glDetachShader_t glDetachShader;
  SYS_API extern app_glDisableVertexAttribArray_t glDisableVertexAttribArray;
  SYS_API extern app_glDrawBuffers_t glDrawBuffers;
  SYS_API extern app_glEnableVertexAttribArray_t glEnableVertexAttribArray;
  SYS_API extern app_glGetActiveAttrib_t glGetActiveAttrib;
  SYS_API extern app_glGetActiveUniform_t glGetActiveUniform;
  SYS_API extern app_glGetAttachedShaders_t glGetAttachedShaders;
  SYS_API extern app_glGetAttribLocation_t glGetAttribLocation;
  SYS_API extern app_glGetProgramInfoLog_t glGetProgramInfoLog;
  SYS_API extern app_glGetProgramiv_t glGetProgramiv;
  SYS_API extern app_glGetShaderInfoLog_t glGetShaderInfoLog;
  SYS_API extern app_glGetShaderiv_t glGetShaderiv;
  SYS_API extern app_glGetShaderSource_t glGetShaderSource;
  SYS_API extern app_glGetUniformLocation_t glGetUniformLocation;
  SYS_API extern app_glGetUniformfv_t glGetUniformfv;
  SYS_API extern app_glGetUniformiv_t glGetUniformiv;
  SYS_API extern app_glGetVertexAttribdv_t glGetVertexAttribdv;
  SYS_API extern app_glGetVertexAttribfv_t glGetVertexAttribfv;
  SYS_API extern app_glGetVertexAttribiv_t glGetVertexAttribiv;
  SYS_API extern app_glGetVertexAttribPointerv_t glGetVertexAttribPointerv;
  SYS_API extern app_glIsProgram_t glIsProgram;
  SYS_API extern app_glIsShader_t glIsShader;
  SYS_API extern app_glLinkProgram_t glLinkProgram;
  SYS_API extern app_glShaderSource_t glShaderSource;
  SYS_API extern app_glStencilFuncSeparate_t glStencilFuncSeparate;
  SYS_API extern app_glStencilMaskSeparate_t glStencilMaskSeparate;
  SYS_API extern app_glStencilOpSeparate_t glStencilOpSeparate;
  SYS_API extern app_glUniform1f_t glUniform1f;
  SYS_API extern app_glUniform1fv_t glUniform1fv;
  SYS_API extern app_glUniform1i_t glUniform1i;
  SYS_API extern app_glUniform1iv_t glUniform1iv;
  SYS_API extern app_glUniform2f_t glUniform2f;
  SYS_API extern app_glUniform2fv_t glUniform2fv;
  SYS_API extern app_glUniform2i_t glUniform2i;
  SYS_API extern app_glUniform2iv_t glUniform2iv;
  SYS_API extern app_glUniform3f_t glUniform3f;
  SYS_API extern app_glUniform3fv_t glUniform3fv;
  SYS_API extern app_glUniform3i_t glUniform3i;
  SYS_API extern app_glUniform3iv_t glUniform3iv;
  SYS_API extern app_glUniform4f_t glUniform4f;
  SYS_API extern app_glUniform4fv_t glUniform4fv;
  SYS_API extern app_glUniform4i_t glUniform4i;
  SYS_API extern app_glUniform4iv_t glUniform4iv;
  SYS_API extern app_glUniformMatrix2fv_t glUniformMatrix2fv;
  SYS_API extern app_glUniformMatrix3fv_t glUniformMatrix3fv;
  SYS_API extern app_glUniformMatrix4fv_t glUniformMatrix4fv;
  SYS_API extern app_glUseProgram_t glUseProgram;
  SYS_API extern app_glValidateProgram_t glValidateProgram;
  SYS_API extern app_glVertexAttrib1d_t glVertexAttrib1d;
  SYS_API extern app_glVertexAttrib1dv_t glVertexAttrib1dv;
  SYS_API extern app_glVertexAttrib1f_t glVertexAttrib1f;
  SYS_API extern app_glVertexAttrib1fv_t glVertexAttrib1fv;
  SYS_API extern app_glVertexAttrib1s_t glVertexAttrib1s;
  SYS_API extern app_glVertexAttrib1sv_t glVertexAttrib1sv;
  SYS_API extern app_glVertexAttrib2d_t glVertexAttrib2d;
  SYS_API extern app_glVertexAttrib2dv_t glVertexAttrib2dv;
  SYS_API extern app_glVertexAttrib2f_t glVertexAttrib2f;
  SYS_API extern app_glVertexAttrib2fv_t glVertexAttrib2fv;
  SYS_API extern app_glVertexAttrib2s_t glVertexAttrib2s;
  SYS_API extern app_glVertexAttrib2sv_t glVertexAttrib2sv;
  SYS_API extern app_glVertexAttrib3d_t glVertexAttrib3d;
  SYS_API extern app_glVertexAttrib3dv_t glVertexAttrib3dv;
  SYS_API extern app_glVertexAttrib3f_t glVertexAttrib3f;
  SYS_API extern app_glVertexAttrib3fv_t glVertexAttrib3fv;
  SYS_API extern app_glVertexAttrib3s_t glVertexAttrib3s;
  SYS_API extern app_glVertexAttrib3sv_t glVertexAttrib3sv;
  SYS_API extern app_glVertexAttrib4Nbv_t glVertexAttrib4Nbv;
  SYS_API extern app_glVertexAttrib4Niv_t glVertexAttrib4Niv;
  SYS_API extern app_glVertexAttrib4Nsv_t glVertexAttrib4Nsv;
  SYS_API extern app_glVertexAttrib4Nub_t glVertexAttrib4Nub;
  SYS_API extern app_glVertexAttrib4Nubv_t glVertexAttrib4Nubv;
  SYS_API extern app_glVertexAttrib4Nuiv_t glVertexAttrib4Nuiv;
  SYS_API extern app_glVertexAttrib4Nusv_t glVertexAttrib4Nusv;
  SYS_API extern app_glVertexAttrib4bv_t glVertexAttrib4bv;
  SYS_API extern app_glVertexAttrib4d_t glVertexAttrib4d;
  SYS_API extern app_glVertexAttrib4dv_t glVertexAttrib4dv;
  SYS_API extern app_glVertexAttrib4f_t glVertexAttrib4f;
  SYS_API extern app_glVertexAttrib4fv_t glVertexAttrib4fv;
  SYS_API extern app_glVertexAttrib4iv_t glVertexAttrib4iv;
  SYS_API extern app_glVertexAttrib4s_t glVertexAttrib4s;
  SYS_API extern app_glVertexAttrib4sv_t glVertexAttrib4sv;
  SYS_API extern app_glVertexAttrib4ubv_t glVertexAttrib4ubv;
  SYS_API extern app_glVertexAttrib4uiv_t glVertexAttrib4uiv;
  SYS_API extern app_glVertexAttrib4usv_t glVertexAttrib4usv;
  SYS_API extern app_glVertexAttribPointer_t glVertexAttribPointer;
#endif

#ifndef GL_VERSION_2_1
  #define GL_VERSION_2_1 1
  #define APP_GL_VERSION_2_1_DEFINED

  #define GL_CURRENT_RASTER_SECONDARY_COLOR                                    0x845F
  #define GL_PIXEL_PACK_BUFFER                                                 0x88EB
  #define GL_PIXEL_UNPACK_BUFFER                                               0x88EC
  #define GL_PIXEL_PACK_BUFFER_BINDING                                         0x88ED
  #define GL_PIXEL_UNPACK_BUFFER_BINDING                                       0x88EF
  #define GL_FLOAT_MAT2x3                                                      0x8B65
  #define GL_FLOAT_MAT2x4                                                      0x8B66
  #define GL_FLOAT_MAT3x2                                                      0x8B67
  #define GL_FLOAT_MAT3x4                                                      0x8B68
  #define GL_FLOAT_MAT4x2                                                      0x8B69
  #define GL_FLOAT_MAT4x3                                                      0x8B6A
  #define GL_SRGB                                                              0x8C40
  #define GL_SRGB8                                                             0x8C41
  #define GL_SRGB_ALPHA                                                        0x8C42
  #define GL_SRGB8_ALPHA8                                                      0x8C43
  #define GL_SLUMINANCE_ALPHA                                                  0x8C44
  #define GL_SLUMINANCE8_ALPHA8                                                0x8C45
  #define GL_SLUMINANCE                                                        0x8C46
  #define GL_SLUMINANCE8                                                       0x8C47
  #define GL_COMPRESSED_SRGB                                                   0x8C48
  #define GL_COMPRESSED_SRGB_ALPHA                                             0x8C49
  #define GL_COMPRESSED_SLUMINANCE                                             0x8C4A
  #define GL_COMPRESSED_SLUMINANCE_ALPHA                                       0x8C4B

  typedef void (SYS_APIENTRY *app_glUniformMatrix2x3fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniformMatrix2x4fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniformMatrix3x2fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniformMatrix3x4fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniformMatrix4x2fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );
  typedef void (SYS_APIENTRY *app_glUniformMatrix4x3fv_t)( GLint location, GLsizei count, GLboolean transpose, const GLfloat* value );

  SYS_API extern app_glUniformMatrix2x3fv_t glUniformMatrix2x3fv;
  SYS_API extern app_glUniformMatrix2x4fv_t glUniformMatrix2x4fv;
  SYS_API extern app_glUniformMatrix3x2fv_t glUniformMatrix3x2fv;
  SYS_API extern app_glUniformMatrix3x4fv_t glUniformMatrix3x4fv;
  SYS_API extern app_glUniformMatrix4x2fv_t glUniformMatrix4x2fv;
  SYS_API extern app_glUniformMatrix4x3fv_t glUniformMatrix4x3fv;
#endif


SYS_API bool_t app_checkglversion( app_glversion_t glversion );
SYS_API app_glversion_t app_getglversion();


#ifdef __cplusplus
}
#endif


/*============================================================================================================================================================*/
/*                                                                                                                                                            */
/*============================================================================================================================================================*/
/*       1         2         3         4         5         6         7         8         9         0         1         2         3         4         5        */
/*345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678*/
/*============================================================================================================================================================*/


#endif
