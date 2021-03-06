#pragma once

#include "dynet/model.h"
#include "dynet/lstm.h"

namespace dytools
{

struct BiLSTMSettings
{
    unsigned stacks = 1u;
    unsigned layers = 1u;
    unsigned dim = 128u;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        ar & stacks;
        ar & layers;
        ar & dim;
    }

    unsigned int output_rows(const unsigned input_dim) const;
};

struct BiLSTMBuilder
{
    const BiLSTMSettings settings;
    dynet::ParameterCollection local_pc;
    const unsigned input_dim;

    std::vector<std::pair<dynet::VanillaLSTMBuilder, dynet::VanillaLSTMBuilder>> builders;

    BiLSTMBuilder(dynet::ParameterCollection& pc, const BiLSTMSettings& settings, unsigned input_dim);

    void new_graph(dynet::ComputationGraph& cg, bool training, bool update);
    std::vector<dynet::Expression> operator()(const std::vector<dynet::Expression>& embeddings);

    unsigned output_rows() const;
};

}