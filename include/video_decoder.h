/*****************************************************************************
 * video_decoder.h : video decoder thread
 * (c)1999 VideoLAN
 *****************************************************************************
 *****************************************************************************
 * Requires:
 *  "config.h"
 *  "common.h"
 *  "mtime.h"
 *  "vlc_thread.h"
 *  "input.h"
 *  "video.h"
 *  "video_output.h"
 *  "decoder_fifo.h"
 *****************************************************************************/

/*****************************************************************************
 * vdec_thread_t: video decoder thread descriptor
 *****************************************************************************
 * ??
 *****************************************************************************/
typedef struct vdec_thread_s
{
    /* Thread properties and locks */
    boolean_t           b_die;                                 /* `die' flag */
    boolean_t           b_run;                                 /* `run' flag */
    boolean_t           b_error;                             /* `error' flag */
    boolean_t           b_active;                           /* `active' flag */
    vlc_thread_t        thread_id;                /* id for thread functions */

    /* Thread configuration */
    /* ?? */
 /*??*/
//    int *pi_status;

#ifdef OLD_DECODER
    /* Input properties */
    decoder_fifo_t      fifo;                              /* PES input fifo */

    /* The bit stream structure handles the PES stream at the bit level */
    bit_stream_t        bit_stream;

    /* Output properties */
    vout_thread_t *     p_vout;                       /* video output thread */
    int                 i_stream;                         /* video stream id */
#else
    /* idct iformations */
    dctelem_t              p_pre_idct[64*64];

    /* Input properties */
    struct vpar_thread_s *    p_vpar;                 /* video_parser thread */

    /* Lookup tables */
//#ifdef MPEG2_COMPLIANT
    u8              pi_crop_buf[VDEC_CROPRANGE];
    u8 *            pi_crop;
//#endif
#endif
        
#ifdef STATS
    /* Statistics */
    count_t         c_loops;                              /* number of loops */
    count_t         c_idle_loops;                    /* number of idle loops */
#ifdef OLD_DECODER
    count_t         c_pictures;                   /* number of pictures read */
    count_t         c_i_pictures;               /* number of I pictures read */
    count_t         c_p_pictures;               /* number of P pictures read */
    count_t         c_b_pictures;               /* number of B pictures read */    
#endif
    count_t         c_decoded_pictures;        /* number of pictures decoded */
    count_t         c_decoded_i_pictures;    /* number of I pictures decoded */
    count_t         c_decoded_p_pictures;    /* number of P pictures decoded */
    count_t         c_decoded_b_pictures;    /* number of B pictures decoded */
#endif
} vdec_thread_t;

/*****************************************************************************
 * Function pointers
 *****************************************************************************/
#ifndef OLD_DECODER
typedef void (*f_addb_t)( vdec_thread_t *, dctelem_t*, yuv_data_t*, int );
#endif

/*****************************************************************************
 * Prototypes
 *****************************************************************************/
#ifndef OLD_DECODER
struct vpar_thread_s;
#endif

/* Thread management functions */
#ifdef OLD_DECODER
p_vdec_thread_t  vdec_CreateThread       ( /* video_cfg_t *p_cfg, */ input_thread_t *p_input /*,
                                          vout_thread_t *p_vout, int *pi_status */ );
void             vdec_DestroyThread      ( vdec_thread_t *p_vdec /*, int *pi_status */ );
#else
vdec_thread_t * vdec_CreateThread       ( struct vpar_thread_s *p_vpar /*, int *pi_status */ );
void vdec_DestroyThread      ( vdec_thread_t *p_vdec /*, int *pi_status */ );
void vdec_AddBlock( vdec_thread_t *, dctelem_t*, yuv_data_t*, int );
void vdec_CopyBlock( vdec_thread_t *, dctelem_t*, yuv_data_t*, int );
void vdec_DummyBlock( vdec_thread_t *, dctelem_t*, yuv_data_t*, int );
#endif
