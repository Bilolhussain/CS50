import cs50
import argparse
import re
import sys
import nltk
from nltk.tokenize import sent_tokenize


def lines(a, b):
    # Return lines in both a and b
    s1 = set(a.splitlines())  # this gives us a set of unique lines
    s2 = set(b.splitlines())  # this gives us a set of unique lines

    s3 = list(set(s1 & s2))  # makes a list of lines present in both sets
    return s3


def sentences(a, b):
    # Return sentences in both a and b

    sent_1 = set(nltk.sent_tokenize(a))  # this gives us a set of unique sentences
    sent_2 = set(nltk.sent_tokenize(b))  # this gives us a set of unique sentences

    list_1 = list(set(sent_1 & sent_2))  # makes a list of sentences present in both sets
    return list_1


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    list3 = []
    list4 = []

    for i in range(0, len(a) - n + 1):
        list3.append((a[i: i + n]))

    for i in range(0, len(b) - n + 1):
        list4.append((b[i: i + n]))

    sub1 = set((list3)) & set((list4))
    sub1 = list(set(sub1))
    return sub1
