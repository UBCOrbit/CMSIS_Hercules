#
# ARM CMSIS R5 Makefile
# Copyright (C) 2022 James F Dougherty <jfd@cs.stanford.edu>
# 
#

# Target R5F CPU of RPU in ZynqMP
LIBNAME=cmsis.a
CMSIS_CFLAGS = -Wno-ignored-attributes
CMSIS_CFLAGS += -DFPU_PRESENT -Wno-comment  -Wno-implicit-function-declaration
CMSIS_CFLAGS += -DDARM_MATH_MATRIX_CHECK -DARM_MATH_ROUNDING
EXTRA_CFLAGS = -IInclude -I. $(CMSIS_CFLAGS)

# Source files for core library
SRCS=Source/SupportFunctions/arm_copy_f32.c\
     Source/SupportFunctions/arm_copy_q31.c\
     Source/SupportFunctions/arm_copy_q15.c\
     Source/SupportFunctions/arm_copy_q7.c\
     Source/SupportFunctions/arm_fill_f32.c\
     Source/SupportFunctions/arm_fill_q31.c\
     Source/SupportFunctions/arm_fill_q15.c\
     Source/SupportFunctions/arm_fill_q7.c\
     Source/SupportFunctions/arm_float_to_q15.c\
     Source/SupportFunctions/arm_float_to_q31.c\
     Source/SupportFunctions/arm_float_to_q7.c\
     Source/SupportFunctions/arm_q15_to_float.c\
     Source/SupportFunctions/arm_q15_to_q31.c\
     Source/SupportFunctions/arm_q15_to_q7.c\
     Source/SupportFunctions/arm_q31_to_float.c\
     Source/SupportFunctions/arm_q31_to_q15.c\
     Source/SupportFunctions/arm_q31_to_q7.c\
     Source/SupportFunctions/arm_q7_to_float.c\
     Source/SupportFunctions/arm_q7_to_q15.c\
     Source/SupportFunctions/arm_q7_to_q31.c\
     Source/BasicMathFunctions/arm_abs_f32.c\
     Source/BasicMathFunctions/arm_dot_prod_q15.c\
     Source/BasicMathFunctions/arm_negate_q31.c\
     Source/BasicMathFunctions/arm_scale_q7.c\
     Source/BasicMathFunctions/arm_abs_q15.c\
     Source/BasicMathFunctions/arm_dot_prod_q31.c\
     Source/BasicMathFunctions/arm_negate_q7.c\
     Source/BasicMathFunctions/arm_shift_q15.c\
     Source/BasicMathFunctions/arm_abs_q31.c\
     Source/BasicMathFunctions/arm_dot_prod_q7.c\
     Source/BasicMathFunctions/arm_offset_f32.c\
     Source/BasicMathFunctions/arm_shift_q31.c\
     Source/BasicMathFunctions/arm_abs_q7.c\
     Source/BasicMathFunctions/arm_mult_f32.c\
     Source/BasicMathFunctions/arm_offset_q15.c\
     Source/BasicMathFunctions/arm_shift_q7.c\
     Source/BasicMathFunctions/arm_add_f32.c\
     Source/BasicMathFunctions/arm_mult_q15.c\
     Source/BasicMathFunctions/arm_offset_q31.c\
     Source/BasicMathFunctions/arm_sub_f32.c\
     Source/BasicMathFunctions/arm_add_q15.c\
     Source/BasicMathFunctions/arm_mult_q31.c\
     Source/BasicMathFunctions/arm_offset_q7.c\
     Source/BasicMathFunctions/arm_sub_q15.c\
     Source/BasicMathFunctions/arm_add_q31.c\
     Source/BasicMathFunctions/arm_mult_q7.c\
     Source/BasicMathFunctions/arm_scale_f32.c\
     Source/BasicMathFunctions/arm_sub_q31.c\
     Source/BasicMathFunctions/arm_add_q7.c\
     Source/BasicMathFunctions/arm_negate_f32.c\
     Source/BasicMathFunctions/arm_scale_q15.c\
     Source/BasicMathFunctions/arm_sub_q7.c\
     Source/BasicMathFunctions/arm_dot_prod_f32.c\
     Source/BasicMathFunctions/arm_negate_q15.c\
     Source/BasicMathFunctions/arm_scale_q31.c\
     Source/CommonTables/arm_common_tables.c\
     Source/ComplexMathFunctions/arm_cmplx_conj_f32.c\
     Source/ComplexMathFunctions/arm_cmplx_mag_f32.c\
     Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.c\
     Source/ComplexMathFunctions/arm_cmplx_conj_q15.c\
     Source/ComplexMathFunctions/arm_cmplx_mag_q15.c\
     Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.c\
     Source/ComplexMathFunctions/arm_cmplx_conj_q31.c\
     Source/ComplexMathFunctions/arm_cmplx_mag_q31.c\
     Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.c\
     Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.c\
     Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c\
     Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.c\
     Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.c\
     Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.c\
     Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.c\
     Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.c\
     Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.c\
     Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.c\
     Source/ControllerFunctions/arm_pid_init_f32.c\
     Source/ControllerFunctions/arm_pid_init_q31.c\
     Source/ControllerFunctions/arm_pid_reset_q15.c\
     Source/ControllerFunctions/arm_sin_cos_f32.c\
     Source/ControllerFunctions/arm_pid_init_q15.c\
     Source/ControllerFunctions/arm_pid_reset_f32.c\
     Source/ControllerFunctions/arm_pid_reset_q31.c\
     Source/ControllerFunctions/arm_sin_cos_q31.c\
     Source/FastMathFunctions/arm_cos_f32.c\
     Source/FastMathFunctions/arm_cos_q31.c\
     Source/FastMathFunctions/arm_sin_q15.c\
     Source/FastMathFunctions/arm_sqrt_q15.c\
     Source/FastMathFunctions/arm_cos_q15.c\
     Source/FastMathFunctions/arm_sin_f32.c\
     Source/FastMathFunctions/arm_sin_q31.c\
     Source/FastMathFunctions/arm_sqrt_q31.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_init_q31.c\
     Source/FilteringFunctions/arm_fir_init_q31.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_32x64_q31.c\
     Source/FilteringFunctions/arm_fir_init_q7.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_f32.c\
     Source/FilteringFunctions/arm_fir_interpolate_f32.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_fast_q15.c\
     Source/FilteringFunctions/arm_fir_interpolate_init_f32.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_fast_q31.c\
     Source/FilteringFunctions/arm_fir_interpolate_init_q15.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_init_f32.c\
     Source/FilteringFunctions/arm_fir_interpolate_init_q31.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_init_q15.c\
     Source/FilteringFunctions/arm_fir_interpolate_q15.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_init_q31.c\
     Source/FilteringFunctions/arm_fir_interpolate_q31.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_q15.c\
     Source/FilteringFunctions/arm_fir_lattice_f32.c\
     Source/FilteringFunctions/arm_biquad_cascade_df1_q31.c\
     Source/FilteringFunctions/arm_fir_lattice_init_f32.c\
     Source/FilteringFunctions/arm_biquad_cascade_df2T_f32.c\
     Source/FilteringFunctions/arm_fir_lattice_init_q15.c\
     Source/FilteringFunctions/arm_biquad_cascade_df2T_init_f32.c\
     Source/FilteringFunctions/arm_fir_lattice_init_q31.c\
     Source/FilteringFunctions/arm_conv_f32.c\
     Source/FilteringFunctions/arm_fir_lattice_q15.c\
     Source/FilteringFunctions/arm_conv_fast_q15.c\
     Source/FilteringFunctions/arm_fir_lattice_q31.c\
     Source/FilteringFunctions/arm_conv_fast_q31.c\
     Source/FilteringFunctions/arm_fir_q15.c\
     Source/FilteringFunctions/arm_conv_partial_f32.c\
     Source/FilteringFunctions/arm_fir_q31.c\
     Source/FilteringFunctions/arm_conv_partial_fast_q15.c\
     Source/FilteringFunctions/arm_fir_q7.c\
     Source/FilteringFunctions/arm_conv_partial_fast_q31.c\
     Source/FilteringFunctions/arm_fir_sparse_f32.c\
     Source/FilteringFunctions/arm_conv_partial_q15.c\
     Source/FilteringFunctions/arm_fir_sparse_init_f32.c\
     Source/FilteringFunctions/arm_conv_partial_q31.c\
     Source/FilteringFunctions/arm_fir_sparse_init_q15.c\
     Source/FilteringFunctions/arm_conv_partial_q7.c\
     Source/FilteringFunctions/arm_fir_sparse_init_q31.c\
     Source/FilteringFunctions/arm_conv_q15.c\
     Source/FilteringFunctions/arm_fir_sparse_init_q7.c\
     Source/FilteringFunctions/arm_conv_q31.c\
     Source/FilteringFunctions/arm_fir_sparse_q15.c\
     Source/FilteringFunctions/arm_conv_q7.c\
     Source/FilteringFunctions/arm_fir_sparse_q31.c\
     Source/FilteringFunctions/arm_correlate_f32.c\
     Source/FilteringFunctions/arm_fir_sparse_q7.c\
     Source/FilteringFunctions/arm_correlate_fast_q15.c\
     Source/FilteringFunctions/arm_iir_lattice_f32.c\
     Source/FilteringFunctions/arm_correlate_fast_q31.c\
     Source/FilteringFunctions/arm_iir_lattice_init_f32.c\
     Source/FilteringFunctions/arm_correlate_q15.c\
     Source/FilteringFunctions/arm_iir_lattice_init_q15.c\
     Source/FilteringFunctions/arm_correlate_q31.c\
     Source/FilteringFunctions/arm_iir_lattice_init_q31.c\
     Source/FilteringFunctions/arm_correlate_q7.c\
     Source/FilteringFunctions/arm_iir_lattice_q15.c\
     Source/FilteringFunctions/arm_fir_decimate_f32.c\
     Source/FilteringFunctions/arm_iir_lattice_q31.c\
     Source/FilteringFunctions/arm_fir_decimate_fast_q15.c\
     Source/FilteringFunctions/arm_lms_f32.c\
     Source/FilteringFunctions/arm_fir_decimate_fast_q31.c\
     Source/FilteringFunctions/arm_lms_init_f32.c\
     Source/FilteringFunctions/arm_fir_decimate_init_f32.c\
     Source/FilteringFunctions/arm_lms_init_q15.c\
     Source/FilteringFunctions/arm_fir_decimate_init_q15.c\
     Source/FilteringFunctions/arm_lms_init_q31.c\
     Source/FilteringFunctions/arm_fir_decimate_init_q31.c\
     Source/FilteringFunctions/arm_lms_norm_f32.c\
     Source/FilteringFunctions/arm_fir_decimate_q15.c\
     Source/FilteringFunctions/arm_lms_norm_init_f32.c\
     Source/FilteringFunctions/arm_fir_decimate_q31.c\
     Source/FilteringFunctions/arm_lms_norm_init_q15.c\
     Source/FilteringFunctions/arm_fir_f32.c\
     Source/FilteringFunctions/arm_lms_norm_init_q31.c\
     Source/FilteringFunctions/arm_fir_fast_q15.c\
     Source/FilteringFunctions/arm_lms_norm_q15.c\
     Source/FilteringFunctions/arm_fir_fast_q31.c\
     Source/FilteringFunctions/arm_lms_norm_q31.c\
     Source/FilteringFunctions/arm_fir_init_f32.c\
     Source/FilteringFunctions/arm_lms_q15.c\
     Source/FilteringFunctions/arm_fir_init_q15.c\
     Source/FilteringFunctions/arm_lms_q31.c\
     Source/MatrixFunctions/arm_mat_add_f32.c\
     Source/MatrixFunctions/arm_mat_init_q31.c\
     Source/MatrixFunctions/arm_mat_scale_q15.c\
     Source/MatrixFunctions/arm_mat_add_q15.c\
     Source/MatrixFunctions/arm_mat_inverse_f32.c\
     Source/MatrixFunctions/arm_mat_scale_q31.c\
     Source/MatrixFunctions/arm_mat_add_q31.c\
     Source/MatrixFunctions/arm_mat_mult_f32.c\
     Source/MatrixFunctions/arm_mat_sub_f32.c\
     Source/MatrixFunctions/arm_mat_cmplx_mult_f32.c\
     Source/MatrixFunctions/arm_mat_mult_fast_q15.c\
     Source/MatrixFunctions/arm_mat_sub_q15.c\
     Source/MatrixFunctions/arm_mat_cmplx_mult_q15.c\
     Source/MatrixFunctions/arm_mat_mult_fast_q31.c\
     Source/MatrixFunctions/arm_mat_sub_q31.c\
     Source/MatrixFunctions/arm_mat_cmplx_mult_q31.c\
     Source/MatrixFunctions/arm_mat_mult_q15.c\
     Source/MatrixFunctions/arm_mat_trans_f32.c\
     Source/MatrixFunctions/arm_mat_init_f32.c\
     Source/MatrixFunctions/arm_mat_mult_q31.c\
     Source/MatrixFunctions/arm_mat_trans_q15.c\
     Source/MatrixFunctions/arm_mat_init_q15.c\
     Source/MatrixFunctions/arm_mat_scale_f32.c\
     Source/MatrixFunctions/arm_mat_trans_q31.c\
     Source/StatisticsFunctions/arm_max_f32.c\
     Source/StatisticsFunctions/arm_mean_q15.c\
     Source/StatisticsFunctions/arm_min_q31.c\
     Source/StatisticsFunctions/arm_power_q7.c\
     Source/StatisticsFunctions/arm_std_q15.c\
     Source/StatisticsFunctions/arm_max_q15.c\
     Source/StatisticsFunctions/arm_mean_q31.c\
     Source/StatisticsFunctions/arm_min_q7.c\
     Source/StatisticsFunctions/arm_rms_f32.c\
     Source/StatisticsFunctions/arm_std_q31.c\
     Source/StatisticsFunctions/arm_max_q31.c\
     Source/StatisticsFunctions/arm_mean_q7.c\
     Source/StatisticsFunctions/arm_power_f32.c\
     Source/StatisticsFunctions/arm_rms_q15.c\
     Source/StatisticsFunctions/arm_var_f32.c\
     Source/StatisticsFunctions/arm_max_q7.c\
     Source/StatisticsFunctions/arm_min_f32.c\
     Source/StatisticsFunctions/arm_power_q15.c\
     Source/StatisticsFunctions/arm_rms_q31.c\
     Source/StatisticsFunctions/arm_var_q15.c\
     Source/StatisticsFunctions/arm_mean_f32.c\
     Source/StatisticsFunctions/arm_min_q15.c\
     Source/StatisticsFunctions/arm_power_q31.c\
     Source/StatisticsFunctions/arm_std_f32.c\
     Source/StatisticsFunctions/arm_var_q31.c\
     Source/TransformFunctions/arm_cfft_mag_f32.c\
     Source/TransformFunctions/arm_cfft_radix4_q15.c\
     Source/TransformFunctions/arm_dct4_q31.c\
     Source/TransformFunctions/arm_cfft_mag_q15.c\
     Source/TransformFunctions/arm_cfft_radix4_q31.c\
     Source/TransformFunctions/arm_rfft_f32.c\
     Source/TransformFunctions/arm_cfft_mag_q31.c\
     Source/TransformFunctions/arm_dct4_f32.c\
     Source/TransformFunctions/arm_rfft_init_f32.c\
     Source/TransformFunctions/arm_cfft_radix4_f32.c\
     Source/TransformFunctions/arm_dct4_init_f32.c\
     Source/TransformFunctions/arm_rfft_init_q15.c\
     Source/TransformFunctions/arm_cfft_radix4_init_f32.c\
     Source/TransformFunctions/arm_dct4_init_q15.c\
     Source/TransformFunctions/arm_rfft_init_q31.c\
     Source/TransformFunctions/arm_cfft_radix4_init_q15.c\
     Source/TransformFunctions/arm_dct4_init_q31.c\
     Source/TransformFunctions/arm_rfft_q15.c\
     Source/TransformFunctions/arm_cfft_radix4_init_q31.c\
     Source/TransformFunctions/arm_dct4_q15.c\
     Source/TransformFunctions/arm_rfft_q31.c


CROSS_COMPILE?=armr5-none-eabi-
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
CFLAGS = -DARMR5 -O0 -g3 -c -fmessage-length=0 -mcpu=cortex-r5 -mfloat-abi=hard  -mfpu=vfpv3-d16 -fno-strict-aliasing -ffunction-sections $(EXTRA_CFLAGS)

OBJS = $(patsubst %.c, %.o, $(SRCS))


$(LIBNAME): $(OBJS)
	$(AR) crs $@ $^ 

objs : $(OBJS)

%.o: %.c
	@echo "Compile" $@
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

clean:
	rm -f Source/BasicMathFunctions/*.o
	rm -f Source/CommonTables/*.o
	rm -f Source/ComplexMathFunctions/*.o
	rm -f Source/ControllerFunctions/*.o
	rm -f Source/FastMathFunctions/*.o
	rm -f Source/FilteringFunctions/*.o
	rm -f Source/MatrixFunctions/*.o
	rm -f Source/StatisticsFunctions/*.o
	rm -f Source/SupportFunctions/*.o
	rm -f Source/TransformFunctions/*.o
	rm -f *.a



etags tags TAGS:
	etags -a *.h
	etags -a *.c
