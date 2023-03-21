import unicodedata
from functools import reduce

import numpy as np
import numba as nb

class ZLCircuit:
    def __init__(self, Z, L, circuit_label="", z_label="", l_label=""):
        """
        a filter with an inductor and component with impedance Z in series
        input is measured across the entire circuit, output is measured across the component with impedance Z.
        Z might have a complex impedance.  this probably would violate conservation of something in real life.

        :param Z: the impedance (ohms, complex)
        :param L: the inductance (henries, real)
        """
        self.Z = Z
        self.L = L
        self.circuit_label = circuit_label
        self.z_label = z_label
        self.l_label = l_label

    def __str__(self):
        inductor_schematic_label = f"L{self.l_label} {self.L}H"
        z_schematic_label = f"Z{self.z_label} {self.Z}Ω"

        return (
                schematic_line(f"<--- Vin{self.circuit_label} --->")
                + schematic_line("")
                + schematic_line("", lhs=" )")
                + schematic_line("", lhs=" ) " + inductor_schematic_label)
                + schematic_line("", lhs=" )")
                + schematic_line("", lhs=" )")
                + schematic_line("")
                + schematic_line(z_schematic_label)
                + schematic_line(r"[      ]", lhs="⏺", rhs="⏺", pad_char="-")
                + schematic_line("")
                + schematic_line(f"<--- Vout{self.circuit_label} --->")
        )


def chained_to_state_space(circuits):
    """
    expands the product of the transfer functions of the input circuits into a state space representation
    :param circuits: a list of ZLCircuits
    :return:
    """
    denom = np.ones(len(circuits) + 1, dtype='complex')

    for i, circuit in enumerate(circuits):
        new_lhs = np.zeros(len(circuits) + 1, dtype='complex')
        for j in range(i + 1):
            new_lhs[j] += denom[j] * circuit.Z
            new_lhs[j + 1] += denom[j] * circuit.L
        denom = new_lhs

    highest_order_derivative = len(circuits)
    vout_coeffs = -denom[:-1] / denom[highest_order_derivative]
    vin_coeff = reduce(lambda x, y: x * y, [circuit.Z for circuit in circuits]) / denom[highest_order_derivative]
    return vout_coeffs, vin_coeff


def simulate_chained_circuits(circuits, V_in, duration, sample_rate):
    """
   Simulates a chain of ZLCircuits.  Have fun!
   :param circuits: a list of ZLCircuits
   :param V_in: a list of voltages
   :param duration: the duration of the simulation
   :param sample_rate: the number of samples per second
   :return:
   """

    return simulate_chained_circuits_(len(circuits), *chained_to_state_space(circuits), V_in, duration, sample_rate)

@nb.jit(nopython=True)
def simulate_chained_circuits_(n, vout_coeffs, vin_coeff, V_in, duration, sample_rate):
    times = np.linspace(0, duration, int(duration * sample_rate))
    state = np.zeros(n, dtype='complex')
    output = np.zeros(len(times), dtype='complex')

    A = np.diag(np.ones(n - 1, dtype='complex'), k=1)
    A[-1, :] = vout_coeffs

    B = np.zeros(n, dtype='complex')
    B[-1] = vin_coeff

    # x(t) = A * x(t - 1) + B * u(t)
    h = 1 / sample_rate
    multiplier = h / 24 * (
        A@A@A * h**3 + 4 * A@A * h**2 + 12 * A * h + 24 * np.eye(n)
    ) # rk4

    B_un = np.transpose(np.dot(multiplier, np.transpose(np.outer(V_in, B))))
    xn_coeff = (np.eye(state.shape[0]) + multiplier @ A)

    for i in range(len(times)):
        state = xn_coeff @ state + B_un[i]
        output[i] = state[0]

    return output, times

LINE_LENGTH = 23

def visible_len(s):
    return len(list(filter(lambda c: unicodedata.category(c) != "Mn", s)))


def schematic_line(middle_string, lhs="|", rhs="|", pad_char=" "):
    remaining_length = LINE_LENGTH - visible_len(lhs) - visible_len(rhs) - visible_len(middle_string)
    left_pad = remaining_length // 2
    right_pad = remaining_length - left_pad
    return f"{lhs}{left_pad * pad_char}{middle_string}{right_pad * pad_char}{rhs}\n"