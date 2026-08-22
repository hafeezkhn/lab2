#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/atomic.h>

#define DEVICE_NAME "my_chardev"
#define CLASS_NAME  "my_char_class"
#define BUFFER_SIZE 1024

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lab Student");
MODULE_DESCRIPTION("Extended Character Driver with Open Counter and Device Info");
MODULE_VERSION("1.0");

static dev_t dev_num;
static struct cdev my_cdev;
static struct class *my_class = NULL;
static struct device *my_device = NULL;

static atomic_t open_count = ATOMIC_INIT(0);
static char device_buffer[BUFFER_SIZE];
static size_t data_size = 0;

/* Open Callback */
static int dev_open(struct inode *inodep, struct file *filep)
{
    int major = imajor(inodep);
    int minor = iminor(inodep);
    int current_opens = atomic_inc_return(&open_count);

    pr_info("char_driver: Device opened %d time(s) | Major: %d, Minor: %d\n",
            current_opens, major, minor);
    return 0;
}

/* Release/Close Callback */
static int dev_release(struct inode *inodep, struct file *filep)
{
    pr_info("char_driver: Device closed successfully\n");
    return 0;
}

/* Read Callback */
static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{
    size_t bytes_to_read;

    if (*offset >= data_size)
        return 0; /* EOF */

    bytes_to_read = min(len, (size_t)(data_size - *offset));

    if (copy_to_user(buffer, device_buffer + *offset, bytes_to_read) != 0)
        return -EFAULT;

    *offset += bytes_to_read;
    pr_info("char_driver: Sent %zu bytes to user\n", bytes_to_read);
    return bytes_to_read;
}

/* Write Callback */
static ssize_t dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset)
{
    size_t bytes_to_write = min(len, (size_t)(BUFFER_SIZE - 1));

    if (copy_from_user(device_buffer, buffer, bytes_to_write) != 0)
        return -EFAULT;

    device_buffer[bytes_to_write] = '\0';
    data_size = bytes_to_write;
    *offset += bytes_to_write;

    pr_info("char_driver: Received %zu bytes from user: \"%s\"\n", bytes_to_write, device_buffer);
    return bytes_to_write;
}

static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = dev_open,
    .release = dev_release,
    .read    = dev_read,
    .write   = dev_write,
};

static int __init char_driver_init(void)
{
    int ret;

    /* 1. Dynamically allocate a Major and Minor number */
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        pr_err("char_driver: Failed to allocate major number\n");
        return ret;
    }

    /* 2. Initialize and add the character device to the kernel */
    cdev_init(&my_cdev, &fops);
    my_cdev.owner = THIS_MODULE;
    ret = cdev_add(&my_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        pr_err("char_driver: Failed to add cdev\n");
        return ret;
    }

    /* 3. Create class and device node automatically under /dev/my_chardev */
    my_class = class_create(CLASS_NAME);
    if (IS_ERR(my_class)) {
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(my_class);
    }

    my_device = device_create(my_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(my_device)) {
        class_destroy(my_class);
        cdev_del(&my_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(my_device);
    }

    pr_info("char_driver: Loaded | Major: %d, Minor: %d | Node: /dev/%s\n",
            MAJOR(dev_num), MINOR(dev_num), DEVICE_NAME);
    return 0;
}

static void __exit char_driver_exit(void)
{
    device_destroy(my_class, dev_num);
    class_destroy(my_class);
    cdev_del(&my_cdev);
    unregister_chrdev_region(dev_num, 1);
    pr_info("char_driver: Unloaded successfully\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);