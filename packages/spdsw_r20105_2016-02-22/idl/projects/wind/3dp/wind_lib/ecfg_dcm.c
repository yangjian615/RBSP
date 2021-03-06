#include "ecfg_dcm.h"

#include "windmisc.h"   



int check_econfig_pk_validity(packet *pk);



uchar default_ecfg_data[]= {
0x03,0x0b,0x47,0x00,0xf0,0xe1,0x01,0xe3,0x59,0xe3,0x55,0xe3,0x7f,0xe3,0xdb,0xe3,
0x83,0x03,0x7f,0xe4,0xa4,0xe4,0x00,0x02,0x80,0x00,0x00,0x00,0x8f,0xe6,0xb7,0xe9,
0x05,0xcd,0xf1,0xea,0x75,0xec,0x4c,0xec,0xd6,0xec,0xa9,0xb1,0x3c,0xb2,0xc2,0xd1,
0x11,0xd4,0xb0,0xf2,0xe3,0xc2,0xb0,0xf2,0x00,0x00,0x3c,0x92,0x7b,0xa1,0x00,0x01,
0x01,0x00,0x00,0xf1,0x6f,0xa2,0x00,0x00,0x04,0x03,0x00,0x02,0xa4,0x1f,0x24,0xf4,
0xf2,0xfb,0x00,0x03,0x6a,0x3f,0xc8,0x20,0xff,0xff,0x24,0xf4,0xd0,0xfe,0xd5,0x02,
0xdd,0x85,0xe8,0x03,0xb0,0xda,0x41,0xd5,0x86,0xd7,0x05,0xd7,0x0f,0xdd,0x70,0xdd,
0x65,0xdd,0x33,0xc0,0x04,0xc1,0x6e,0xc2,0xfb,0xca,0x81,0xcd,0x00,0x7c,0x37,0xcb,
0xb0,0xf2,0x60,0xcc,0x88,0xcf,0xac,0xce,0xb0,0xf2,0xb0,0xf2,0xb0,0xf2,0xe7,0x3c
};

#define ECONFIG_SIZE 144



uchar default_excfg_data[] = {
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
0x02,0x02,0x82,0x82,0x82,0x82,0x02,0x02,0x83,0x87,0x0c,0x10,0x13,0x17,0x18,0x18,
0x19,0x18,0x17,0x13,0x10,0x0c,0x87,0x82,0x00,0x05,0x0d,0x14,0x1a,0x1f,0x21,0x22,
0x1f,0x1a,0x14,0x0d,0x04,0x00,0x00,0x00,0x00,0x00,0xac,0xd8,0x43,0xda,0xe3,0xd9,
0xac,0xd8,0xaa,0xab,0xaf,0xff,0x8c,0x00,0x7c,0x00,0x7c,0x00,0x7c,0x00,0x5c,0x00,
0x5c,0x00,0x6c,0x00,0x5c,0x00,0x8c,0x00,0x7c,0x00,0x7c,0x00,0x7c,0x00,0x5c,0x00,
0x5c,0x00,0x6c,0x00,0x5c,0x00,0x34,0x55,0x34,0x55,0x34,0x65,0x34,0x65,0x34,0x44,
0x34,0x44,0x34,0x54,0x34,0x54,0x34,0x55,0x34,0x55,0x34,0x65,0x34,0x65,0x34,0x44,
0x34,0x44,0x34,0x54,0x34,0x54,0x24,0x40,0x24,0x40,0x24,0x50,0x24,0x40,0x24,0x30,
0x24,0x20,0x24,0x30,0x24,0x30,0x24,0x40,0x24,0x40,0x24,0x50,0x24,0x40,0x24,0x30,
0x24,0x20,0x24,0x30,0x24,0x30,0x38,0x38,0x31,0x31,0x30,0x30,0x2a,0x2a,0x53,0x53,
0x20,0x20,0x04,0x04,0x00,0x00,0x8c,0x8c,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x00,0x00,
0x5a,0xa4,0xd3,0x49,0x09,0x00,0x10,0x27,0x04,0x03,0x48,0x00,0x9b,0x41,0x06,0x00,
0x28,0x23,0x04,0x03,0x48,0x00,0x5c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x33,0xc0,0x8e,0xc0,0xb9,0x00,0x05,0xbf,0x04,0x03,0x2b,0xcf,
0xd1,0xe9,0xf3,0xab,0x8e,0x06,0x18,0x00,0x26,0xa1,0xa6,0x00,0xa3,0x22,0x03,0x26,
0xa1,0x94,0x00,0xa3,0x24,0x03,0x26,0xa1,0xa8,0x00,0xa3,0x42,0x03,0x26,0xa1,0x96,
0x00,0xa3,0x44,0x03,0x26,0xa1,0x9c,0x00,0xa3,0x62,0x03,0x26,0xa1,0x8c,0x00,0xa3,
0x64,0x03,0x26,0xa1,0x9e,0x00,0xa3,0x82,0x03,0x26,0xa1,0x90,0x00,0xa3,0x84,0x03,
0x26,0xa1,0xa0,0x00,0xa3,0xa2,0x03,0x26,0xa1,0x98,0x00,0xa3,0xa4,0x03,0x26,0xa1,
0xa2,0x00,0xa3,0xc2,0x03,0x26,0xa1,0x9a,0x05,0x05,0x73,0x07,0x8f,0x15,0xbd,0x03,
0x1d,0x7e,0xff,0xff,0x00,0x00,0x08,0x00,0x00,0x00,0x1f,0x00,0x00,0x20,0x00,0x20,
0x00,0x20,0x00,0x20,0x40,0x03
};
#define EXCONFIG_SIZE 422






/* returns 0 if invalid
/* returns 1 if valid */
int check_econfig_pk_validity(packet *pk)
{
	uint2  checksum;
	int  n;
	uchar *u;

	if(pk ==0)
		return(0);
	if(pk->idtype != 0x1800)
		return(0);
	if(pk->dsize != 144)
		return(0);
	checksum = 256;
	u = pk->data;
	for(n=0;n< (int)pk->dsize -2 ;n+=2,u+=2)
		checksum += str_to_uint2(u);
	if(str_to_uint2(u) != checksum){
                printf("EESA Config Checksum Error at %s: expected %x: received %x\r\n",
                        time_to_YMDHMS(pk->time),checksum,str_to_uint2(u));
		return(0);
	}
	else
		return(1);
}








/**************************************************************
The following routine will decomutate selected elements of an 
EESA configuration packet.  The routine does NOT currently
fill in all elements.
***************************************************************/
int decom_econfig(packet *pk,Econfig *vp)
{
	uchar *s;

	if(pk==0){           /* use default setup */
		vp->time1 = vp->time2 = 0;
		s = default_ecfg_data;
	}
	else{
		vp->time1 = pk->time;
		if(pk->next)
			vp->time2 = pk->next->time;
		else
			vp->time2 = pk->time;
		s = pk->data;
	}

	vp->inst_config = s[0];
	vp->inst_mode   = s[1];
	vp->icfg_size   = s[2];

	vp->esa_swp_high = str_to_uint2(s + 0x12);
	vp->esa_swp_low  = str_to_uint2(s + 0x14);
	vp->min_swp_level  = str_to_uint2(s + 0x16);
	vp->step_swp_level = str_to_uint2(s + 0x18);
	vp->step_time      = str_to_uint2(s + 0x20);

	vp->mcph  = s[0x3c];
	vp->mcpl  = s[0x3d];

	vp->el_sweep.start_E = str_to_uint2(s + 0x4c);
	vp->el_sweep.k_sw    = str_to_uint2(s + 0x4e);
	vp->el_sweep.s1      = str_to_int2(s + 0x50);
	vp->el_sweep.s2      = str_to_int2(s + 0x52);
	vp->el_sweep.m2      = str_to_uint2(s + 0x54);
	vp->el_sweep.gs2     = str_to_uint2(s + 0x56);

	vp->eh_sweep.start_E = str_to_uint2(s + 0x58);
	vp->eh_sweep.k_sw    = str_to_uint2(s + 0x5a);
	vp->eh_sweep.s1      = str_to_int2(s + 0x5c);
	vp->eh_sweep.s2      = str_to_int2(s + 0x5e);
	vp->eh_sweep.m2      = str_to_uint2(s + 0x60);
	vp->eh_sweep.gs2     = str_to_uint2(s + 0x62);

	vp->cp_emom_add      = str_to_uint2(s + 0x7c);

	vp->valid = 1;

	return(1);
}





/* decomutates selected elements of the extended configuration table */
int decom_exconfig(packet *pk,EXconfig *ex)
{
	int i;
	uchar *u;

	if(pk==NULL){
		ex->time1 = ex->time2 = 0;
		u = default_excfg_data;
	}
	else{
		ex->time1 = pk->time;
		if(pk->next)
			ex->time2 = pk->next->time;
		else
			ex->time2 = pk->time;
		u = pk->data;
	}

	for(i=0;i<32;i++)
		ex->p_blank[i] = u[i];
	for(i=0;i<40;i++)
		ex->t_blank[i] = u[i+32];
	for(i=0;i<17;i++){
		ex->arc_cos_def1[i] = u[i+72];
		ex->arc_cos_def2[i] = u[i+89];
	}
	ex->pad_shift = u[0x108];

	ex->valid = 1;
	
	return(1);
}

int4 ecfg_to_idl(int argc,void *argv[])
{
        ecfg_data *ecfg;
        Econfig ec;
        int4 size,advance,index,*options,ok,i;
        double *time;
        static packet_selector pks;
        pklist *pkl;
        packet *pk;

        if(argc == 0)
                return( number_of_packets(E_CFG_ID, 0.,1e12) );
        if(argc != 3 && argc !=2){
                printf("Incorrect number of arguments\r\n");
                return(0);
        }
        options = (int4 *)argv[0];
        time = (double *)argv[1];
        ecfg = (ecfg_data *)argv[2];
        

        size =  options[0];
        advance = options[1];
        index   = options[2];

        if(argc ==2){
            ok = get_time_points(E_CFG_ID,size,time);
            return(ok);
        }

        if(size != sizeof(ecfg_data)){
            printf("Incorrect structure size %d (should be %d).  Aborting.\r\n",size,sizeof(ecfg_data));
            return(0);
        }
	
        if (advance ) {
            SET_PKS_BY_INDEX(pks,pks.index+advance,E_CFG_ID) ;
        }
        else if (index < 0) {    /* negative index means get by time*/
            SET_PKS_BY_LASTT(pks,time[0],E_CFG_ID) ;
        }
        else {
            SET_PKS_BY_INDEX(pks,index,E_CFG_ID) ;
        }
	
	pk = get_packet(&pks);
	ecfg->time = pk->time;
	ecfg->index = pks.index;
	
	for (i=0; i<142; i++)
		ecfg->data[i] = pk->data[i];
	
	decom_econfig(pk,&ec);
	
	ecfg->valid = ec.valid;

        return(1);

}

int4 excfg_to_idl(int argc,void *argv[])
{
        excfg_data *excfg;
        int4 size,advance,index,*options,ok,i;
        double *time;
        static packet_selector pks;
        pklist *pkl;
        packet *pk;

        if(argc == 0)
                return( number_of_packets(E_XCFG_ID, 0.,1e12) );
        if(argc != 3 && argc !=2){
                printf("Incorrect number of arguments\r\n");
                return(0);
        }
        options = (int4 *)argv[0];
        time = (double *)argv[1];
        excfg = (excfg_data *)argv[2];
        

        size =  options[0];
        advance = options[1];
        index   = options[2];

        if(argc ==2){
            ok = get_time_points(E_XCFG_ID,size,time);
            return(ok);
        }

        if(size != sizeof(excfg_data)){
            printf("Incorrect structure size %d (should be %d).  Aborting.\r\n",size,sizeof(excfg_data));
            return(0);
        }
	
        if (advance ) {
            SET_PKS_BY_INDEX(pks,pks.index+advance,E_XCFG_ID) ;
        }
        else if (index < 0) {    /* negative index means get by time*/
            SET_PKS_BY_LASTT(pks,time[0],E_XCFG_ID) ;
        }
        else {
            SET_PKS_BY_INDEX(pks,index,E_XCFG_ID) ;
        }
	
	pk = get_packet(&pks);
	excfg->time = pk->time;
	excfg->index = pks.index;
	
	for (i=0; i<264; i++)
		excfg->data[i] = pk->data[i];
	
	excfg->valid = 1;

        return(1);

}














#if 0
#define NULLNV ((nvector)0)
 = {
0x03,           /*uchar inst_config;		*/
0x68,           /*uchar inst_mode;		*/
0x0032,         /*uint2  icfg_size;		*/
NULLNV,         /*nvector init_inst;		*/
NULLNV,         /*nvector inst_hk;		*/
NULLNV,         /*nvector set_x_hk_mux;		*/
NULLNV,         /*nvector get_x_hk_mux;		*/
NULLNV,         /*nvector cal_command;		*/
NULLNV,         /*nvector esa_swp_select;		*/
0x0383,         /*uint2    sel_sector;		*/
NULLNV,         /*nvector esa_swp_high;		*/
NULLNV,         /*nvector esa_swp_low;		*/
0x0200,         /*uint2    min_swp_level;		*/
0x0080,         /*uint2    step_swp_level;		*/
0x0000,         /*uint2    step_time;		*/
NULLNV,         /*nvector esa_swp_start;		*/
NULLNV,         /*nvector esa_pdq_task;		*/
NULLNV,         /*nvector dumpf_proc;		*/
NULLNV,         /*nvector eos_task0;		*/
NULLNV,         /*nvector rate_proc;		*/
NULLNV,         /*nvector spec_proc;		*/
NULLNV,         /*nvector flux_proc;		*/
NULLNV,         /*nvector pha_proc;		*/
NULLNV,         /*nvector pha_pckt_maker;		*/
NULLNV,         /*nvector sci_init;		*/
NULLNV,         /*nvector sci_proc;		*/
NULLNV,         /*nvector brst_proc;		*/
NULLNV,         /*nvector eos_task1;		*/
NULLNV,         /*nvector tlm_task;		*/
0x0000,         /*uint2    esa_default_swp;		*/
0x3c,           /*uchar   esa_hve;		*/
0x92,           /*uchar   esa_pmt;		*/
0x7b,           /*uchar   esa_mcph;		*/
0xa1,           /*uchar   esa_mcpl;		*/
0x00,           /*uchar   esa_pha_basech;		*/
0x01,           /*uchar   esa_pha_chstp;		*/
0x01,           /*uchar   esa_pha_lvlstp;		*/
0xff,           /*uchar   esa_pha_mnlvl_low;		*/
0x2f,           /*uchar   esa_pha_mnlvl_high;		*/
0x00,           /*uchar   fpc_mode_low;		*/
0x00,           /*uchar   fpc_mode_mid;		*/
0x00,           /*uchar   fpc_mode_high;		*/
0x00,           /*uchar   fpc_chnl;		*/
0x00,           /*uchar   fpc_period;		*/
0x04,           /*uchar   wave_event;		*/
0x03,           /*uchar   wave_period;		*/
0x0200,         /*uint2    min_wave_level;		*/
{     START_E_EL, K_SW_EL, S1_EL, S2_EL, M2_EL, GSHIFT2_EL }, /*  EESAL sweep  */
{     START_E_EH, K_SW_EH, S1_EH, S2_EH, M2_EH, GSHIFT2_EH }, /*  EESAH sweep  */
NULLNV,         /*nvector init_map_add;		*/
NULLNV,         /*nvector acc_3d_add;		*/
NULLNV,         /*nvector mk_3d_pkt_add;		*/
NULLNV,         /*nvector mk_mom_pkt_add;		*/
NULLNV,         /*nvector getb_dir_add;		*/
NULLNV,         /*nvector cosb256_add;		*/
NULLNV,         /*nvector sinb256_add;		*/
NULLNV,         /*nvector init_velw_add;		*/
NULLNV,         /*nvector acc_pad_add;		*/
NULLNV,         /*nvector mk_pad_pkt_add;		*/
NULLNV,         /*nvector cp_bdq_add;		*/
NULLNV,         /*nvector cp_stmom_add;		*/
NULLNV,         /*nvector cp_emom_add;		*/
NULLNV,         /*nvector cp_edens_add;		*/
NULLNV,         /*nvector cp_bst_add;		*/
NULLNV,         /*nvector filter_ptr;		*/
NULLNV,         /*nvector sin_cos_sec_tbl;		*/
NULLNV,         /*nvector w_el_tbl;		*/
NULLNV,         /*nvector init_corr_add;		*/
NULLNV,         /*nvector acc_corr_add;		*/
NULLNV,         /*nvector mk_corr_pkt_add;		*/
0x0000,         /*uint2    check_sum;		*/
};
#endif
#if 0
 = {
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,  /* blanking for spin sector */
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,  /* blanking for low 0-15 */   
	0x04,0x04,0x04,0x04,0x04,0x04,0x04,0x04,
	0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,   /* blanking for high 0-23 */
	0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,  
	0x02,0x02,0x82,0x82,0x82,0x82,0x02,0x02,
	3+128,7+128,12,16,19,23,24,24,25,24,23,19,16,12,7+128,2+128,0,     /* arc cos codes (16) */
	5, 13, 20,26,31,33,34,31,26,20,13,4, 0,0,0,0,  0,  /* arc cos codes (12) */
/*  pad energies resolutions;  make sure that bit 30 is always set!   (1..32)*/
/*   1(x2) 28(x1)        15(x2)       6(x1),6(x2),3(x4)    6(x1),8(x2),2(x4) */
	0x3ffffffe,        0x2aaaaaaa,        0x3faaa888,        0x3faaaa88,
/*	map_mom_g, map_45d_g, map_cut_g, map11c_g, */
	NULLNV,    NULLNV   , NULLNV,    NULLNV,
	0xaa,    0xab,    0xaf,    0xff, 
#if 1
	0x008c,  0x007c,  0x007c,  0x007c,  0x005c,  0x005c,  0x006c,  0x005c,
	0x008c,  0x007c,  0x007c,  0x007c,  0x005c,  0x005c,  0x006c,  0x005c,
	0x3385,  0x2285,  0x4485,  0x3385,  0x3385,  0x2285,  0x3385,  0x2285,
	0x3385,  0x2285,  0x4485,  0x3385,  0x3385,  0x2285,  0x3385,  0x2285,
	0x4024,  0x4024,  0x5024,  0x4024,  0x3024,  0x2024,  0x3024,  0x3024,
	0x4024,  0x4024,  0x5024,  0x4024,  0x3024,  0x2024,  0x3024,  0x3024,

	0x38,    0x38  ,  0x26  ,  0x26  ,  0x30  ,  0x30  ,
	0x2a,    0x2a  ,  0x53  ,  0x53  ,  0x20  ,  0x20  ,
	0x04,    0x04  ,  0x00  ,  0x00  ,  0x8c  ,  0x8c  ,
	0x1f,    0x1f  ,  0x1f  ,  0x1f  ,  0x1f  ,  0x1f  ,
#else
	0x008c,  0x007c,  0x007c,  0x007c,  0x005c,  0x005c,  0x006c,  0x005c,
	0x008c,  0x007c,  0x007c,  0x007c,  0x005c,  0x005c,  0x006c,  0x005c,
	0x2285,  0x2285,  0x2285,  0x2285,  0x2285,  0x2285,  0x2285,  0x2285,
	0x2285,  0x2285,  0x2285,  0x2285,  0x2285,  0x2285,  0x2285,  0x2285,
	0x3024,  0x3024,  0x3024,  0x3024,  0x3024,  0x3024,  0x3024,  0x3024,
	0x3024,  0x3024,  0x3024,  0x3024,  0x3024,  0x3024,  0x3024,  0x3024,

	0x38,    0x38  ,  0x26  ,  0x26  ,  0x30  ,  0x30  ,
	0x2a,    0x2a  ,  0x53  ,  0x53  ,  0x20  ,  0x20  ,
	0x04,    0x04  ,  0x00  ,  0x00  ,  0x8c  ,  0x8c  ,
	0x1f,    0x1f  ,  0x1f  ,  0x1f  ,  0x1f  ,  0x1f  ,
#endif

	0, 21562, 0 ,100, 0 ,100,   /* up deflector */
	0, 21562, 0 ,100, 0 ,100,   /* down deflector */

	0,   /* bph_offset;	*/  /* rotation value for Bph  */
	90,  /* bth_offset;	*/  /*  typically 90 */
	-92, /* bth_mult;*/  /* for conversion from degrees to binary degrees */
	0,   /* misc_bits;		*/
	0,   /* defl_up_offset;		*/
	0,   /* defl_dn_offset;		*/
	92,  /* pad_shift;		*/           /*  92 for EESAH;  ?? for EESAL */
	0,   /* defl_b_shift;		*/
	0,   /* def_cal_strt;		*/
	0,   /* def_cal_step;		*/
	0,   /* def_cal_ehdac;		*/
{ 0xffff,  0,    3, 2, 4,  48,   190,  11  },
{ 0xffff,  0,    3, 2, 4,  48,   190,  11  },
};
#endif
