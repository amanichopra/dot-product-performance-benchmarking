import numpy as np
import argparse
import time

def dp(N, A, B):
    R = 0.0
    for j in range(N):
        R += A[j] * B[j]
    return R

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('vector_size', type=int)
    parser.add_argument('num_reps', type=int)
    parser.add_argument('-v', '--verbose', type=bool, default=False)

    args = parser.parse_args()

    A = np.ones(args.vector_size, dtype=np.float32)
    B = np.ones(args.vector_size, dtype=np.float32)

    total_time = 0

    for i in range(args.num_reps):
        start = time.monotonic()
        dp_result = dp(len(A), A, B)
        end = time.monotonic()

        if i > args.num_reps / 2:
            total_time += (end - start)
            
    
    if args.verbose: 
        print(f'Dot Product Result: {dp_result}')
        print()

    avg_time = total_time / (args.num_reps / 2)

    bw = 2 * len(A) * (8 / 1E9) / avg_time
    flops = 2 * len(A) / avg_time

    print(f"N: {len(A)}   <T>: {avg_time} sec   B: {bw} GB/sec   F: {flops} FLOP/sec\n")

if __name__ == '__main__':
    main()

