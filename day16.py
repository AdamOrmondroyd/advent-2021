from numpy import log2, floor, longdouble, prod, sum, amin, amax, array, append


def reverse_bits(bits, length=None):
    if 0 == bits:
        return 0
    result = int(bin(bits)[:1:-1], base=2)
    if length is not None:
        result *= 2 ** (length - int(floor(log2(longdouble(bits)))) - 1)
    return result


def gt(a):
    return int(a[0] > a[1])


def lt(a):
    return int(a[0] < a[1])


def eq(a):
    return int(a[0] == a[1])


operator_map = {
    0: sum,
    1: prod,
    2: amin,
    3: amax,
    5: gt,
    6: lt,
    7: eq,
}


# these masks are to be used on the reversed packet
three_bit_mask = 7  # 111
packet_type_mask = 56  # 111000
four_bit_mask = 30  # 11110
fifteen_bit_mask = 2 ** 15 - 1
eleven_bit_mask = 2 ** 11 - 1

with open("input16.txt") as file:

    line = file.read()  # .splitlines()
    # print(line)
    packet = int(line, base=16)
    print(bin(packet))
    # exit()
    reversed_packet = reverse_bits(packet, len(line) * 4)
    print(bin(reversed_packet))

    sum_versions = 0

    def parse(reversed_packet):

        print(bin(reversed_packet))
        # print("call")
        if reversed_packet != 0:
            version_number = reverse_bits(reversed_packet & three_bit_mask, 3)
            reversed_packet >>= 3
            packet_type_ID = reverse_bits(reversed_packet & three_bit_mask, 3)
            reversed_packet >>= 3
            print(f"version {version_number}, packet type {packet_type_ID}")
            global sum_versions
            sum_versions += version_number

            if 4 == packet_type_ID:
                literal_value = 0
                found_end = False
                while not found_end:
                    literal_value <<= 4
                    literal_value += reverse_bits(
                        (reversed_packet & four_bit_mask) >> 1, 4
                    )
                    if 0 == reversed_packet & 1:
                        found_end = True
                    reversed_packet >>= 5
                print(f"literal value: {literal_value}")

                return literal_value, reversed_packet

            else:
                operator = operator_map[packet_type_ID]
                results = array([])
                length_type_ID = reversed_packet & 1
                reversed_packet >>= 1
                if length_type_ID:  # 1
                    print(11)
                    num_sub_packets = reverse_bits(
                        reversed_packet & eleven_bit_mask, 11
                    )
                    reversed_packet >>= 11
                    print(f"num sub packets {num_sub_packets}")
                    for i in range(num_sub_packets):
                        number, reversed_packet = parse(reversed_packet)
                        results = append(results, number)
                else:  # 0

                    print(15)
                    len_sub_packets = reverse_bits(
                        reversed_packet & fifteen_bit_mask, 15
                    )
                    reversed_packet >>= 15
                    print(f"len sub packets {len_sub_packets}")

                    subpackets = reversed_packet & (2 ** len_sub_packets - 1)
                    reversed_packet >>= len_sub_packets

                    while subpackets != 0:

                        number, subpackets = parse(subpackets)
                        results = append(results, number)

                return operator(results), reversed_packet
        return 0, reversed_packet

    result, _ = parse(reversed_packet)
    print(f"sum of version numbers {sum_versions}")
    print(f"result: {int(result)}")
