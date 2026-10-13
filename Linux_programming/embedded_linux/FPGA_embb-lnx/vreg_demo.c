// Minimal virtual register demo as a linux kernel module
//Purpose: demonstrate character devices and sysfs without real hardware

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/mutex.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Minimal virtual register demo: /dev + sysfs attributes");

//"Registers" fake registers (RAM backed) 
static u32 reg_ctrl;
static u32 reg_status;
static u32 reg_period = 0x000000FF;
static u32 reg_duty;
static DEFINE_MUTEX(reg_lock);


//Helpers: parse/print u32 as text (accepts decimal or 0x...)
static int parse_u32(const char *buf, size_t count, u32 *out)
{
    unsigned long val;
    int ret;
    char kbuf[32];
    size_t n = min(count, sizeof(kbuf) - 1);
    memcpy(kbuf, buf, n);
    kbuf[n] = '\0';
    
    ret = kstrtoul(kbuf, 0, &val);
    if (ret)
        return ret;

    *out = (u32)val;
    return 0;
}


//character device : read shows a snapshot of all registers as text
static ssize_t vreg_read(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
    char buf[128];
    int n;
    u32 c, p , d , s:

    mutex_lock(&reg_lock);
    c = reg_ctrl;
    p = reg_period;
    d = reg_duty;
    s = reg_status;
    mutex_unlock(&reg_lock);

    n = snprintf(buf, sizeof(buf),
                 "CTRL: 0x%08X\nSTATUS: 0x%08X\nPERIOD: 0x%08X\nDUTY: 0x%08X\n",
                 c, s, p, d);
    return simple_read_from_buffer(buf, count, ppos, buf, n);
}

static ssize_t vreg_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    //no-op for this demo, but could parse input to set registers
    return len;
}

static const struct file_operations vreg_fops = {
    .owner = THIS_MODULE,
    .read = vreg_read,
    .write = vreg_write,
};

static struct miscdevice vreg_miscdev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "vreg",
    .fops = &vreg_fops,
};


//Sysfs attributes for each register
static ssize_t ctrl_show(struct device *dev, struct device_attribute *attr, char *buf)
{   
    u32 val;
    mutex_lock(&reg_lock);
    val = reg_ctrl;
    mutex_unlock(&reg_lock);
    return sprintf(buf, "0x%08X\n", val);
}

static DEVICE_ATTR_RW(ctrl);

static ssize_t period_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    u32 val;
    mutex_lock(&reg_lock);
    val = reg_period;
    mutex_unlock(&reg_lock);
    return sprintf(buf, "0x%08X\n", val);
}

static DEVICE_ATTR_RW(period);  

static ssize_t duty_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    u32 val;
    mutex_lock(&reg_lock);
    val = reg_duty;
    mutex_unlock(&reg_lock);
    return sprintf(buf, "0x%08X\n", val);
}
static  DEVICE_ATTR_RW(duty);

static ssize_t status_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    u32 val;
    mutex_lock(&reg_lock);
    val = reg_status;
    mutex_unlock(&reg_lock);
    return sprintf(buf, "0x%08X\n", val);
}
static DEVICE_ATTR_RO(status);

static struct attribute *vreg_attrs[] = {
    &dev_attr_ctrl.attr,
    &dev_attr_period.attr,
    &dev_attr_duty.attr,
    &dev_attr_status.attr,
    NULL,
};

static struct attribute_group vreg_attr_group = {
    .attrs = vreg_attrs,
};

static int __init vreg_init(void)
{
    int ret;

    ret = misc_register(&vreg_miscdev);
    if (ret) {
        pr_err("Failed to register misc device\n");
        return ret;
    }

    ret = sysfs_create_group(&vreg_miscdev.this_device->kobj, &vreg_attr_group);
    if (ret) {
        pr_err("Failed to create sysfs group\n");
        misc_deregister(&vreg_miscdev);
        return ret;
    }

    pr_info("vreg module loaded\n");
    return 0;
}

static void __exit vreg_exit(void)
{
    sysfs_remove_group(&vreg_miscdev.this_device->kobj, &vreg_attr_group);
    misc_deregister(&vreg_miscdev);
    pr_info("vreg module unloaded\n");
}

module_init(vreg_init);
module_exit(vreg_exit);