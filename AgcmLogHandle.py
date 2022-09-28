#  Copyright (c) Kirky-X. 2022. All rights reserved.
#
# 用于对比AGCM在ARM平台和x86平台精度差异，需配合对应的日志输出函数使用
# @Author   : Kirky-X
# @Time     : 2022/9/26
# @File     : AgcmLogHandle.py
# @Software: PyCharm
import re
import types

# 用于存储Arm平台日志的数据，{flag:{param:md5,...},...}
data_dict_arm: dict = {}
# 用于存储Arm平台日志的数据，{flag:{param:md5,...},...}
data_dict_x86: dict = {}


def read_log(log_file: str, is_arm: bool) -> None:
    # 读取日志文件，并将数据存储到字典中
    # 并且输出存在差异的变量
    # @log_file  : 日志文件的路径
    # @is_arm    : 判断是否是ARM架构的日志文件，用于将数据存储在不同的字典中
    dict_now: dict
    if is_arm:
        dict_now = data_dict_arm
    else:
        dict_now = data_dict_x86
    pattern = re.compile(r"\[ '(.*?)' ] md5sum of this array (.*?) is :(.*?)\n")
    with open(log_file, "r", encoding="utf-8") as f:
        for line in f.readlines():
            # flag日志输出的开头
            if line[0] == '[':
                # 处理数据格式
                find_res = pattern.findall(line)
                if len(find_res) == 0:
                    continue
                temp = find_res[0]
                value = temp[2].replace(" ", "")
                # 正则匹配不规范的数据，直接舍弃
                pattern_2 = re.compile(r"\[|]|'|sum|is|array| ")
                if len(temp[0]) < 2 or len(pattern_2.findall(temp[0])) > 0 or \
                        len(pattern_2.findall(temp[1])) or \
                        len(value) > 32 or len(value) < 32:
                    continue
                direct = {temp[1]: value}
                # 加入字典中
                temp_dict = dict_now.get(temp[0])
                if isinstance(temp_dict, types.NoneType):
                    # 字典中不存在值，直接插入数据进行初始化
                    dict_now.update({temp[0]: direct})
                else:
                    # 存在值的情况，再进行判断值是否相等
                    temp_dictItem = temp_dict.get(temp[1])
                    if isinstance(temp_dictItem, types.NoneType):
                        # 字典中不存在值，直接插入数据进行初始化
                        temp_dict.update(direct)
                    else:
                        # 值不相等则输出
                        # 针对单台机器的多个线程跑同一程序，值应相等，不相等则表示机器本身出现问题
                        if temp_dictItem != value:
                            print("There is difference===>" + temp[0] + "\tParameter=>" +
                                  temp[1] + "\tLatest value=>" + value +
                                  "\tPrevious value=>" + temp_dictItem)


def find_diff_between_arm_with_x86() -> None:
    # 根据Arm和x86存在差异的地方
    # data_dict_arm 和 data_dict_x86 中的所有的key应该是全部相同的
    for key in data_dict_arm.keys():
        dict_arm_item: dict = data_dict_arm.get(key)
        dict_x86_item: dict = data_dict_x86.get(key)
        for item_key in dict_arm_item.keys():
            arm_value = dict_arm_item.get(item_key)
            x86_value = dict_x86_item.get(item_key)
            if arm_value != x86_value:
                print("\n↓ ↓ ↓ There is difference between ARM and x86! ↓ ↓ ↓" +
                      "\nFlag => " + key +
                      "\nParameter => " + item_key +
                      "\nArm value => " + arm_value +
                      "\nx86 value => " + x86_value + "\n")


def log_slim(log_file: str) -> None:
    read_log(log_file, is_arm=True)
    slim_log = log_file.split(".")[0] + "-slim.log"
    with open(slim_log, "w", encoding="utf-8") as f:
        for flag in data_dict_arm.keys():
            print("flag===>" + flag)
            dict_item: dict = data_dict_arm.get(flag)
            for param in dict_item.keys():
                print("param===>" + param)
                value: str = dict_item.get(param)
                f.write("[ '{}' ] md5sum of this array {} is :{} \n".format(flag, param, value))


def main() -> None:
    print("-*-*-*-*-*-*-*-  dual  -*-*-*-*-*-*-*-*-")
    # read_log("aqcm_21708.log", is_arm=True)
    # read_log("agcm-out.log", is_arm=False)
    # find_diff_between_arm_with_x86()
    log_slim("aqcm_21914.log")
    print("-*-*-*-*-*-*-*-  done  -*-*-*-*-*-*-*-*-")


if __name__ == "__main__":
    main()
