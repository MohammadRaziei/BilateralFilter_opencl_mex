kernel void simple_add(global const int *A, global const int *B,
                       global int *C) {
  for (int i = get_global_id(0); i < 10; i += get_global_size(0)) {
    C[i] = A[i] + B[i];
  }
}
