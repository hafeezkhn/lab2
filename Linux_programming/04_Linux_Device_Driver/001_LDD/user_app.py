def main():
    driver_handle = open("/proc/ldd", "r")
    message_from_kernel = driver_handle.readline()
    print(message_from_kernel)
    driver_handle.close()
    return

main()  