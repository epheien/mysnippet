/*                                                     
 * 字符设备模板
 */                                                    
#include <linux/init.h>
#include <linux/module.h>

#include <linux/kernel.h>	/* printk() */
#include <linux/slab.h>		/* kmalloc() */
#include <linux/fs.h>		/* file ops, etc. */
#include <linux/errno.h>	/* error code */
#include <linux/types.h>	/* size_t */
#include <linux/kdev_t.h>	/* MKDEV(), MAJOR(), MINOR() */
#include <linux/cdev.h>		/* character device */
#include <asm/uaccess.h>	/* copy_*_user */

#define DRV_NAME	"chrdev"
#define DRV_VERSION	"1.0"
#define DRV_DESCRIPTION	"A simple character device module"
#define DRV_AUTHOR	"(C) 2012-2013 eph <epheien@163.com>"

/* 环形缓冲区 */
static char *g_ring_buff = NULL;
/* 环形缓冲区环的尺寸 */
static unsigned long g_ring_buff_size = 1024;
module_param_named(size, g_ring_buff_size, ulong, 0644);
MODULE_PARM_DESC(size, "ring buffer size");

static int chrdev_major = 0;
module_param_named(major, chrdev_major, int, 0644);
MODULE_PARM_DESC(major, "device major number");

/* 字符设备结构 */
static struct cdev chrdev;

static int chrdev_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int chrdev_release(struct inode *inode, struct file *filp)
{
	return 0;
}

/* 
 * 返回:
 * < 0	错误
 * 0	到达文件尾部
 * > 0	传输成功的数目
 * */
static ssize_t chrdev_read(struct file *filp, char __user *buf, size_t count,
			   loff_t *f_pos)
{
	if (count > g_ring_buff_size)
		count = g_ring_buff_size;

	if (copy_to_user(buf, g_ring_buff, count))
		return -EFAULT;

	/* 读完之后，清空 */
	/*memset(g_ring_buff, 0, g_ring_buff_size);*/

	/* 暂时只支持一次读取 */
	return 0;
}

/* 
 * 返回:
 * < 0	错误
 * >= 0	写入的数量，如果调用者发现返回值小于 count，则会重复调用
 * */
static ssize_t chrdev_write(struct file *filp, const char __user *buf,
			    size_t count, loff_t *f_pos)
{
	if (count > g_ring_buff_size)
		return -EINVAL;

	/* 暂时只支持写开头部分 */
	if (copy_from_user(g_ring_buff, buf, count))
		return -EFAULT;

	f_pos += count;

	return count;
}

static struct file_operations chrdev_ops = {
	.owner		= THIS_MODULE,
	.open		= chrdev_open,
	.release	= chrdev_release,
	.read		= chrdev_read,
	.write		= chrdev_write,
};

static int chrdev_setup(struct cdev *dev, struct file_operations *fops)
{
	int err = 0;
	int devno = MKDEV(chrdev_major, 0);

	cdev_init(dev, fops);
	dev->owner = THIS_MODULE;
	/*dev->ops = fops;*/
	err = cdev_add(dev, devno, 1);
	if (err < 0)
		return err;

	g_ring_buff = kmalloc(g_ring_buff_size, GFP_KERNEL);
	if (!g_ring_buff) {
		cdev_del(dev);
		return -ENOMEM;
	}
	memset(g_ring_buff, 0, g_ring_buff_size);

	return 0;
}

static int __init chrdev_init(void)
{
	int result = 0;
	dev_t devno = MKDEV(chrdev_major, 0);

	if (chrdev_major) {
		/* 指定分配，注册设备号 */
		result = register_chrdev_region(devno, 1, DRV_NAME);
	} else {
		/* 动态分配 */
		result = alloc_chrdev_region(&devno, 0, 1, DRV_NAME);
	}

	if (result < 0) {
		printk(KERN_WARNING "%s: failed to get major %d\n",
		       DRV_NAME, chrdev_major);
		return result;
	}

	if (chrdev_major == 0) {
		chrdev_major = MAJOR(devno);
	}

	result = chrdev_setup(&chrdev, &chrdev_ops);
	if (result < 0) {
		printk(KERN_WARNING "%s: failed to register cdev\n", DRV_NAME);
		unregister_chrdev_region(MKDEV(chrdev_major, 0), 1);
		return result;
	}

	printk(KERN_INFO "%s: major=%d\n", DRV_NAME, chrdev_major);
	return 0;
}

static void __exit chrdev_exit(void)
{
	cdev_del(&chrdev);
	kfree(g_ring_buff);
	unregister_chrdev_region(MKDEV(chrdev_major, 0), 1);
}

module_init(chrdev_init);
module_exit(chrdev_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_VERSION(DRV_VERSION);
