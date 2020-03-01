from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # Split file (string type) to a list containing each line as an element
    # convert lists to set in order to utilise the Set.intersection() method
    # Set.intersection() returns mutual elements
    mutualLines = set(a.split("\n")).intersection(set(b.split("\n")))

    return list(mutualLines)


def sentences(a, b):
    """Return sentences in both a and b"""
    sentA = set(sent_tokenize(a))
    sentB = set(sent_tokenize(b))

    mutualSent = sentA.intersection(sentB)

    return list(mutualSent)


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    ssA = {a[i:n+i] for i in range(0, len(a) - n + 1)}
    ssB = {b[i:n+i] for i in range(0, len(b) - n + 1)}

    mutualSS = list(ssA.intersection(ssB))

    return mutualSS
