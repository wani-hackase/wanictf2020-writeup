logo = """
:::::::..   .::::::.   :::.
;;;;``;;;; ;;;`    `   ;;`;;
 [[[,/[[[' '[==/[[[[, ,[[ '[[,
 $$$$$$c     '''    $c$$$cc$$$c
 888b "88bo,88b    dP 888   888,
 MMMM   "W"  "YMmMY"  YMM   ""`
"""
description = [
    """
+================================+
| Given : p, q (512-bit integer) |
| Find  : n = p*q                |
+================================+
""",
    """
+=======================================+
| Given : m ) Message                   |
|         e ) Public exponent           |
|         n ) p*q  (p, q 512-bit prime) |
| Find  : c = m**e (mod n)              |
+=======================================+
""",
    """
+=====================================+
| Given :  p, q ) 512-bit primes      |
|          e    ) Public exponent     |
|          c    ) Encrypted message   |
|                 = m**e (mod p*q)    |
| Find  :  m    ) Message             |
+=====================================+
""",
]


flag = "FLAG{y0uv3_und3rst00d_t3xtb00k_RSA}"
