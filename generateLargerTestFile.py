import pandas as pd
import numpy as np

# ------------------------------------------------------------------
# Row notes (0-based index, excluding header):
#
# NULL VALUE ROWS:
# Row 3   -> NULL in Age
# Row 7   -> NULL in Score
# Row 12  -> NULL in Name
#
# DUPLICATE ROWS:
# Row 15  -> Duplicate of Row 1
# Row 16  -> Duplicate of Row 5
# Row 17  -> Duplicate of Row 9
#
# Total rows: 20
# ------------------------------------------------------------------

data = {
    "ID": [
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 13, 14, 15,
        2, 6, 10, 16, 17
    ],
    "Name": [
        "Alice", "Bob", "Charlie", "David", "Eva",
        "Frank", "Grace", "Helen", "Ian", "Jane",
        "Karl", "Liam", None, "Nina", "Oscar",
        "Bob", "Frank", "Jane", "Paul", "Quinn"
    ],
    "Age": [
        25, 30, 35, None, 28,
        40, 33, 29, 45, 38,
        41, 27, 31, 36, 50,
        30, 40, 38, 26, 34
    ],
    "Score": [
        88, 92.5, 79, 85, 90.0,
        76, 84.5, None, 91, 87.0,
        89, 73.5, 95, 82, 88.5,
        92.5, 76, 87.0, 80, 86.5
    ]
}

df = pd.DataFrame(data)

# Save CSV to current directory
df.to_csv("ScriptTestFile.csv", index=False)

print("ScriptTestFile.csv with 20 rows has been generated in the current directory.")