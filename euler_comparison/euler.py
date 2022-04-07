import numpy as np
import time


# decorator for measuring time
def measure_time(func):
    # measuring time method, time.perf_counter() -> @mcoding
    # https://youtu.be/qUeud6DvOWI?t=337
    def time_wrapper(*args, **kwargs):
        start = time.perf_counter()
        func(*args, **kwargs)
        end = time.perf_counter()
        print(f"Python Language: Elapsed: {end-start} seconds\n")
    return time_wrapper


def euler(derivative,
          delta_t: float,
          x_init: float, y_init: float,
          x_limit: float) -> tuple:
    """
    Euler's formula required to create an approximation to the function.
    y1 = y0 + m*(x1-x0)
    m = dy/dx,
        m is f'(y0), modify the derivative depends on the needs
    ---
    Arguments:
        derivative  (function) : m, function object of the derivative function
        x_init      (float)    : x0 -> initial value of x
        y_init      (float)    : y0 -> initial value of y
        delta_t     (float)    : delta_t -> the time step
        x_limit     (float)    : x_limit -> end point of the function

    Returns:
        x axis, y axis (tuple) : x_res, y_res
    """
    x_res, y_res = [x_init], [y_init]
    # x0: calculated x value
    # y0: calculated y value
    x0, y0 = x_init, y_init
    y1 = None
    for x0 in np.arange(x0, x_limit, delta_t):
        y1 = y0 + derivative(y0)*delta_t
        x_res.append(x0+delta_t)
        y_res.append(y1)
        y0 = y1
    return (x_res, y_res)


def y_prime(y: float) -> float:
    return 0.7 * y * (1-y/750) - 20


@measure_time
def run_test():
    for i in range(100):
        x, y = euler(derivative=y_prime, delta_t=2, x_init=0,
                     y_init=30, x_limit=30)


if __name__ == '__main__':
    run_test()
    # Python Language - Elapsed: 0.0011363619705662131 seconds
    # C      Language - Elapsed: 0.000066 seconds

    # terminal Python Language - Elapsed: 0.0010130290174856782 seconds
    # terminal C Language      - Elapsed: 0.000271 seconds
