#include<linux/init.h>
#include<linux/module.h>
#include<linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hk");
MODULE_DESCRIPTION("A Simple LDD");


static ssize_t	ldd_read(struct file *file_pointer, char __user *buf, size_t count, loff_t *offset){
   char msg[] = "Hello from LDD\n";
   size_t len = strlen(msg);
   int result = 0;

   result = copy_to_user(buf, msg, len);

   *offset += len;
   if(*offset >= len )
        return 0;

    printk(KERN_INFO "ldd_read invoked\n");

    return len;  
}


static struct proc_dir_entry *proc_node;
struct proc_ops driver_proc_ops = {
    .proc_read = ldd_read, //action to be performed when read is invoked on proc file
};
static int __init ldd_init(void)
{
    printk(KERN_INFO "Entry\n");
    proc_node = proc_create("ldd_1", 0, NULL, &driver_proc_ops);
    printk(KERN_INFO "Exit\n");
    return 0;
}

static void __exit ldd_exit(void)
{
    printk(KERN_INFO "Goodbye entry\n");
    proc_remove(proc_node);
    printk(KERN_INFO "Goodbye exit\n");
}



module_init(ldd_init);
module_exit(ldd_exit);
