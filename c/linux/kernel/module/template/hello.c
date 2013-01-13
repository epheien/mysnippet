/*                                                     
 * $Id: hello.c,v 1.5 2004/10/26 03:32:21 corbet Exp $ 
 */                                                    
#include <linux/init.h>
#include <linux/module.h>

#define DRV_NAME	"hello"
#define DRV_VERSION	"1.0"
#define DRV_DESCRIPTION	"hello module"
#define DRV_AUTHOR	"(C) 2012-2013 eph <epheien@163.com>"

static int __init hello_init(void)
{
	printk(KERN_ALERT "Hello, world\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR(DRV_AUTHOR);
MODULE_DESCRIPTION(DRV_DESCRIPTION);
MODULE_VERSION(DRV_VERSION);
