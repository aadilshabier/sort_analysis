#!/usr/env/python3

import matplotlib.pyplot as plt
from pathlib import Path
import json

sorters: list = [
    "quicksort1",
    "quicksort2",
    "quicksort3",
    "radixsort",
    "insertionsort",
    "mergesort",
    "heapsort",
]

lineformats: dict = {
    "quicksort1": "^-",
    "quicksort2": ">-",
    "quicksort3": "<-",
    "radixsort": "o--",
    "insertionsort": "8-",
    "mergesort": "s-",
    "heapsort": "P--",
}

datagens: list = [
    "inc",
    "rand",
    "dec",
]

DATA_DIR: str = "data/"
DATA_PATH = Path(DATA_DIR)

def read_ints(filepath):
    with filepath.open() as file:
        _ = file.readline()
        data = [int(x) for x in file.read().split("\n") if x]
    return data

def read_floats(filepath):
    with filepath.open() as file:
        _ = file.readline()
        data = [float(x) for x in file.read().split("\n") if x]
    return data

def main():
    filepath = DATA_PATH / "array_sizes.txt"
    xs = read_ints(filepath)

    data = {datagen: {} for datagen in datagens}
    for datagen in datagens:
        for sorter in sorters:
            filepath = DATA_PATH / f"{datagen}_{sorter}.txt"
            data[datagen][sorter] = read_floats(filepath)
            
    # print(json.dumps(xs))
    # print(json.dumps(data, indent=4))

    fig, axs = plt.subplots(1, len(datagens))
    for i, datagen in enumerate(datagens):
        axs[i].set_title(datagen)
        for sorter in sorters:
            ys = data[datagen][sorter]
            axs[i].plot(xs, ys, lineformats[sorter], label=sorter)
            axs[i].set_xlabel("Number of elements")
            axs[i].set_ylabel("Time (ms)")
        axs[i].legend()
    plt.show()

if __name__ == "__main__":
    main()
