#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_roots.h>

typedef double db;

typedef struct {
	db a, b, c, d, e, f;
}poly_params;

db get_val(db x, void *params)
{
	poly_params *p = (poly_params*) params;
	return ((((p->a * x + p->b) * x + p->c) * x + p->d) * x + p->e) * x + p->f;
}

db get_deriv(db x, void *params)
{
	poly_params *p = (poly_params*) params;
	return (((5 * p->a * x + 4 * p->b) * x + 3 * p->c) * x + 2 * p->d) * x + p->e;
}

void get_fdf(db x, void *params, db *y, db *dy)
{
	*y = get_val(x, params);
	*dy = get_deriv(x, params);
}

int f_solve(gsl_function *f, db r_expected, db x_lo, db x_hi, db eps)
{
	int status;
	int iter = 0, max_iter = 100;
	db r = 0;
	const gsl_root_fsolver_type *T;
	gsl_root_fsolver *s;
	T = gsl_root_fsolver_bisection;
	s = gsl_root_fsolver_alloc (T);
	gsl_root_fsolver_set(s, f, x_lo, x_hi);
	
	printf ("using %s method\n", 
			gsl_root_fsolver_name (s));
	
	printf ("%5s [%9s, %9s] %9s %10s %9s\n",
			"iter", "lower", "upper", "root", 
			"err", "err(est)");
	
	do {
		iter++;
		status = gsl_root_fsolver_iterate (s);
		r = gsl_root_fsolver_root (s);
		x_lo = gsl_root_fsolver_x_lower (s);
		x_hi = gsl_root_fsolver_x_upper (s);
		status = gsl_root_test_interval (x_lo, x_hi, 0, eps);
	
		if (status == GSL_SUCCESS)
			printf ("Converged:\n");
	
		printf ("%5d [%.7f, %.7f] %.7f %+.7f %.7f\n",
			iter, x_lo, x_hi,
			r, r - r_expected, 
			x_hi - x_lo);
	} while (status == GSL_CONTINUE && iter < max_iter);

	gsl_root_fsolver_free (s);
	return status;
}

int fdf_solve(gsl_function_fdf *fdf, db r_expected, db x, db eps)
{
	int status;
	int iter = 0, max_iter = 100;
	db x0 = 0;
	const gsl_root_fdfsolver_type *T;
	gsl_root_fdfsolver *s;
	T = gsl_root_fdfsolver_newton;
	s = gsl_root_fdfsolver_alloc (T);
	gsl_root_fdfsolver_set(s, fdf, x);
	
	printf ("using %s method\n",
			gsl_root_fdfsolver_name (s));

	printf ("%-5s %10s %10s %10s\n",
	        "iter", "root", "err", "err(est)");
	
	do {
		iter++;
		status = gsl_root_fdfsolver_iterate (s);
		x0 = x;
		x = gsl_root_fdfsolver_root (s);
		status = gsl_root_test_delta (x, x0, 0, eps);
		
		if (status == GSL_SUCCESS)
	    	printf ("Converged:\n");
		
	    printf ("%5d %10.7f %+10.7f %10.7f\n",
	    		iter, x, x - r_expected, x - x0);
	  } while (status == GSL_CONTINUE && iter < max_iter);
	
	gsl_root_fdfsolver_free (s);
	return status;
}

int main()
{
	db r_expected = -1;
	db x_lo = -exp(1), x_hi = 0, x = 0, eps = 1e-5;
 	poly_params params = {8, 1, 0, 9, 7, 5};
	
	gsl_function F;
	F.function = &get_val;
	F.params = 0;
	F.params = &params;
	
	gsl_function_fdf FDF;
	FDF.f = &get_val;
	FDF.df = &get_deriv;
	FDF.fdf = &get_fdf;
	FDF.params = &params;
	
//	return f_solve(&F, r_expected, x_lo, x_hi, eps);
	return fdf_solve(&FDF, r_expected, x, eps);
}
