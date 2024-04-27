import ocnn
import torch

from solver import Solver, Dataset, parse_args
import numpy as np

class ClsSolver(Solver):
  def get_model(self, flags):
    if flags.name.lower() == 'lenet':
      model = ocnn.LeNet(flags.depth, flags.channel, flags.nout)
    elif flags.name.lower() == 'resnet':
      model = ocnn.ResNet(flags.depth, flags.channel, flags.nout,
                          flags.resblock_num)
    else:
      raise ValueError
    return model

  def get_dataset(self, flags):
    transform = ocnn.TransformCompose(flags)
    dataset = Dataset(flags.location, flags.filelist, transform, in_memory=True)
    return dataset, ocnn.collate_octrees

  def train_step(self, batch):
    octree, label = batch['octree'].cuda(), batch['label'].cuda()
    logits = self.model(octree)
    log_softmax = torch.nn.functional.log_softmax(logits, dim=1)
    loss = torch.nn.functional.nll_loss(log_softmax, label)
    pred = torch.argmax(logits, dim=1)

    # accu_nums = pred.eq(label).float()
    # n_correct = accu_nums.sum().item()
    # n_total = accu_nums.size(dim=0)

    accu = pred.eq(label).float().mean()
    return {'train/loss': loss, 'train/accu': accu}

  def test_step(self, batch, acc_mat):
    octree, label = batch['octree'].cuda(), batch['label'].cuda()
    logits = self.model(octree)
    log_softmax = torch.nn.functional.log_softmax(logits, dim=1)
    loss = torch.nn.functional.nll_loss(log_softmax, label)
    pred = torch.argmax(logits, dim=1)

    for i in range(label.shape[0]):
      predi = pred[i].item()
      true = label[i].item()
      acc_mat[predi, true] += 1
    # accu_nums = pred.eq(label).float()
    # n_correct = accu_nums.sum().item()
    # n_total = accu_nums.size(dim=0)

    accu = pred.eq(label).float().mean()
    # print("test/accu" + str(accu))
    return {'test/loss': loss, 'test/accu': accu}


def main(TheSolver):
  FLAGS = parse_args()
  Solver.main(FLAGS, TheSolver)


if __name__ == "__main__":
  main(ClsSolver)
