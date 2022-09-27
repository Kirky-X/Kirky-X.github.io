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
dataDictArm: dict = {}
# 用于存储Arm平台日志的数据，{flag:{param:md5,...},...}
dataDictX86: dict = {}


def readLog(logFile: str, isArm: bool) -> None:
    # 读取日志文件，并将数据存储到字典中
    # 并且输出存在差异的变量
    # @logFile  : 日志文件的路径
    # @isArm    : 判断是否是ARM架构的日志文件，用于将数据存储在不同的字典中
    dictNow: dict
    if isArm:
        dictNow = dataDictArm
    else:
        dictNow = dataDictX86
    pattern = re.compile(r"\[ '(.*?)' ] md5sum of this array (.*?) is :(.*?)\n")
    with open(logFile, "r", encoding="utf-8") as f:
        for line in f.readlines():
            # flag日志输出的开头
            if line[0] == '[':
                # 处理数据格式
                temp = pattern.findall(line)[0]
                value = temp[2].replace(" ", "")
                direct = {temp[1]: value}
                # 加入字典中
                tempDict = dictNow.get(temp[0])
                if isinstance(tempDict, types.NoneType):
                    # 字典中不存在值，直接插入数据进行初始化
                    dictNow.update({temp[0]: direct})
                else:
                    # 存在值的情况，再进行判断值是否相等
                    tempDictItem = tempDict.get(temp[1])
                    if isinstance(tempDictItem, types.NoneType):
                        # 字典中不存在值，直接插入数据进行初始化
                        tempDict.update(direct)
                    else:
                        # 值不相等则输出
                        # 针对单台机器的多个线程跑同一程序，值应相等，不相等则表示机器本身出现问题
                        if tempDictItem != value:
                            print("There is difference===>" + temp[0] + "\tParameter=>" +
                                  temp[1] + "\tLatest value=>" + value +
                                  "\tPrevious value=>" + tempDictItem)


def findDiffInArmWithX86() -> None:
    # 根据Arm和x86存在差异的地方
    # dataDictArm 和 dataDictX86 中的所有的key应该是全部相同的
    for key in dataDictArm.keys():
        dictArmItem: dict = dataDictArm.get(key)
        dictX86Item: dict = dataDictX86.get(key)
        for itemKey in dictArmItem.keys():
            armValue = dictArmItem.get(itemKey)
            x86Value = dictX86Item.get(itemKey)
            if armValue != x86Value:
                print("\n↓ ↓ ↓ There is difference between ARM and x86! ↓ ↓ ↓" +
                      "\nFlag => " + key +
                      "\nParameter => " + itemKey +
                      "\nArm value => " + armValue +
                      "\nx86 value => " + x86Value + "\n")


def main() -> None:
    print("-*-*-*-*-*-*-*-  dual  -*-*-*-*-*-*-*-*-")
    readLog("aqcm_21708.log", isArm=True)
    readLog("agcm-out.log", isArm=False)
    findDiffInArmWithX86()
    print("-*-*-*-*-*-*-*-  done  -*-*-*-*-*-*-*-*-")


if __name__ == "__main__":
    main()
