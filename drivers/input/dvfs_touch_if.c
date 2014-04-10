/*
 * Author: Alucard_24 <alucard_24 XDA>
 *
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cpufreq.h>
#include <linux/cpu.h>
#include <linux/dvfs_touch_if.h>

atomic_t dvfs_boost_mode = ATOMIC_INIT(2);
atomic_t dvfs_min_limit = ATOMIC_INIT(DVFS_MIN_TOUCH_LIMIT);
atomic_t dvfs_min_high_limit = ATOMIC_INIT(DVFS_MIN_TOUCH_HIGH_LIMIT);
atomic_t dvfs_min_limit_second = ATOMIC_INIT(DVFS_MIN_TOUCH_LIMIT_SECOND);
atomic_t dvfs_min_high_limit_second = ATOMIC_INIT(DVFS_MIN_TOUCH_HIGH_LIMIT_SECOND);
atomic_t syn_off_time = ATOMIC_INIT(SYN_TOUCH_BOOSTER_OFF_TIME);
atomic_t syn_chg_time = ATOMIC_INIT(SYN_TOUCH_BOOSTER_CHG_TIME);
atomic_t syn_high_off_time = ATOMIC_INIT(SYN_TOUCH_BOOSTER_HIGH_OFF_TIME);
atomic_t syn_high_chg_time = ATOMIC_INIT(SYN_TOUCH_BOOSTER_HIGH_CHG_TIME);
atomic_t mxts_off_time = ATOMIC_INIT(MXTS_TOUCH_BOOSTER_OFF_TIME);
atomic_t cyp_off_time = ATOMIC_INIT(CYP_TOUCH_BOOSTER_OFF_TIME);
atomic_t cyp_chg_time = ATOMIC_INIT(CYP_TOUCH_BOOSTER_CHG_TIME);

static ssize_t show_dvfs_boost_mode(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&dvfs_boost_mode));
}

static ssize_t show_dvfs_min_limit(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&dvfs_min_limit));
}

static ssize_t show_dvfs_min_high_limit(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&dvfs_min_high_limit));
}

static ssize_t show_dvfs_min_limit_second(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&dvfs_min_limit_second));
}

static ssize_t show_dvfs_min_high_limit_second(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&dvfs_min_high_limit_second));
}

static ssize_t show_syn_off_time(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&syn_off_time));
}

static ssize_t show_syn_chg_time(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&syn_chg_time));
}

static ssize_t show_syn_high_off_time(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&syn_high_off_time));
}

static ssize_t show_syn_high_chg_time(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&syn_high_chg_time));
}

static ssize_t show_mxts_off_time(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&mxts_off_time));
}

static ssize_t show_cyp_off_time(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&cyp_off_time));
}

static ssize_t show_cyp_chg_time(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
	return sprintf(buf, "%d\n", atomic_read(&cyp_chg_time));
}

static ssize_t store_dvfs_boost_mode(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	if (input != 0 && input != 1 && input != 2 && input != 9)
		input = 0;

	if (input != atomic_read(&dvfs_boost_mode)) {
		/* update only if valid value provided */
		atomic_set(&dvfs_boost_mode,input);
	}

	return count;
}

static ssize_t store_dvfs_min_limit(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 1890000),810000);

	if (input != atomic_read(&dvfs_min_limit)) {
		/* update only if valid value provided */
		atomic_set(&dvfs_min_limit,input);
	}

	return count;
}

static ssize_t store_dvfs_min_high_limit(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 1890000),810000);

	if (input != atomic_read(&dvfs_min_high_limit)) {
		/* update only if valid value provided */
		atomic_set(&dvfs_min_high_limit,input);
	}

	return count;
}

static ssize_t store_dvfs_min_limit_second(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 1350000),486000);

	if (input != atomic_read(&dvfs_min_limit_second)) {
		/* update only if valid value provided */
		atomic_set(&dvfs_min_limit_second,input);
	}

	return count;
}

static ssize_t store_dvfs_min_high_limit_second(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 1350000),486000);

	if (input != atomic_read(&dvfs_min_high_limit_second)) {
		/* update only if valid value provided */
		atomic_set(&dvfs_min_high_limit_second,input);
	}

	return count;
}

static ssize_t store_syn_off_time(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 5000),200);

	if (input !=  atomic_read(&syn_off_time)) {
		/* update only if valid value provided */
		atomic_set(&syn_off_time,input);
	}

	return count;
}

static ssize_t store_syn_chg_time(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 1000),100);

	if (input != atomic_read(&syn_chg_time)) {
		/* update only if valid value provided */
		atomic_set(&syn_chg_time, input);
	}

	return count;
}

static ssize_t store_syn_high_off_time(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 5000),200);

	if (input !=  atomic_read(&syn_high_off_time)) {
		/* update only if valid value provided */
		atomic_set(&syn_high_off_time,input);
	}

	return count;
}

static ssize_t store_syn_high_chg_time(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 1000),100);

	if (input != atomic_read(&syn_high_chg_time)) {
		/* update only if valid value provided */
		atomic_set(&syn_high_chg_time, input);
	}

	return count;
}

static ssize_t store_mxts_off_time(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 1000),100);

	if (input !=  atomic_read(&mxts_off_time)) {
		/* update only if valid value provided */
		atomic_set(&mxts_off_time,input);
	}

	return count;
}

static ssize_t store_cyp_off_time(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 5000),200);

	if (input !=  atomic_read(&cyp_off_time)) {
		/* update only if valid value provided */
		atomic_set(&cyp_off_time,input);
	}

	return count;
}

static ssize_t store_cyp_chg_time(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{

	int input;
	int ret;

	ret = sscanf(buf, "%d", &input);
	if (ret != 1) {
		return -EINVAL;
	}

	input = max(min(input, 1000),100);

	if (input != atomic_read(&cyp_chg_time)) {
		/* update only if valid value provided */
		atomic_set(&cyp_chg_time, input);
	}

	return count;
}

static struct kobj_attribute dvfs_boost_mode_attr =
	__ATTR(dvfs_boost_mode, 0666, show_dvfs_boost_mode,
			store_dvfs_boost_mode);

static struct kobj_attribute dvfs_min_limit_attr =
	__ATTR(dvfs_min_limit, 0666, show_dvfs_min_limit,
			store_dvfs_min_limit);

static struct kobj_attribute dvfs_min_high_limit_attr =
	__ATTR(dvfs_min_high_limit, 0666, show_dvfs_min_high_limit,
			store_dvfs_min_high_limit);

static struct kobj_attribute dvfs_min_limit_second_attr =
	__ATTR(dvfs_min_limit_second, 0666, show_dvfs_min_limit_second,
			store_dvfs_min_limit_second);

static struct kobj_attribute dvfs_min_high_limit_second_attr =
	__ATTR(dvfs_min_high_limit_second, 0666, show_dvfs_min_high_limit_second,
			store_dvfs_min_high_limit_second);

static struct kobj_attribute syn_off_time_attr =
	__ATTR(syn_off_time, 0666, show_syn_off_time,
			store_syn_off_time);

static struct kobj_attribute syn_chg_time_attr =
	__ATTR(syn_chg_time, 0666, show_syn_chg_time,
			store_syn_chg_time);

static struct kobj_attribute syn_high_off_time_attr =
	__ATTR(syn_high_off_time, 0666, show_syn_high_off_time,
			store_syn_high_off_time);

static struct kobj_attribute syn_high_chg_time_attr =
	__ATTR(syn_high_chg_time, 0666, show_syn_high_chg_time,
			store_syn_high_chg_time);

static struct kobj_attribute mxts_off_time_attr =
	__ATTR(mxts_off_time, 0666, show_mxts_off_time,
			store_mxts_off_time);

static struct kobj_attribute cyp_off_time_attr =
	__ATTR(cyp_off_time, 0666, show_cyp_off_time,
			store_cyp_off_time);

static struct kobj_attribute cyp_chg_time_attr =
	__ATTR(cyp_chg_time, 0666, show_cyp_chg_time,
			store_cyp_chg_time);

static struct attribute *dvfs_touch_if_attrs[] = {
	&dvfs_boost_mode_attr.attr,
	&dvfs_min_limit_attr.attr,
	&dvfs_min_high_limit_attr.attr,
	&dvfs_min_limit_second_attr.attr,
	&dvfs_min_high_limit_second_attr.attr,
	&syn_off_time_attr.attr,
	&syn_chg_time_attr.attr,
	&syn_high_off_time_attr.attr,
	&syn_high_chg_time_attr.attr,
	&mxts_off_time_attr.attr,
	&cyp_off_time_attr.attr,
	&cyp_chg_time_attr.attr,
	NULL,
};

static struct attribute_group dvfs_touch_if_attr_group = {
	.attrs = dvfs_touch_if_attrs,
	.name = "dvfs_touch_if",
};

int __init dvfs_touch_if_init(void)
{
	int rc;

	rc = sysfs_create_group(kernel_kobj, &dvfs_touch_if_attr_group);

	if (rc) {
		pr_info("%s sysfs create failed!\n", __FUNCTION__);
	}

	return (rc);
}

void __exit dvfs_touch_if_exit(void)
{
}

MODULE_AUTHOR("Alucard_24 XDA");
MODULE_DESCRIPTION("DVFS Touch booster interface ver. 3.0");
MODULE_LICENSE("GPL");
module_init(dvfs_touch_if_init);
module_exit(dvfs_touch_if_exit);
